#include <no_opencv_detection.h>
#include <cast_to_grey.h>

NoOpenCVDetection::NoOpenCVDetection(cv::Size params,
                                     int threshold,
                                     cv::Size dilate_kernel_size,
                                     size_t frames,
                                     cv::Size blur_kernel_size,
                                     int max_deviation,
                                     int patience,
                                     int max_elapsed_time,
                                     int my_kernel_size)
                                     : AbstractMotionDetection(std::move(params),
                                                               threshold,
                                                               std::move(dilate_kernel_size),
                                                               frames,
                                                               std::move(blur_kernel_size),
                                                               max_deviation,
                                                               patience,
                                                               max_elapsed_time),
                                                               _blur(9, 3.0)
                                                               {
                                                                    for (size_t i = 0; i < _params.height; ++i)
                                                                    {
                                                                        _visited.emplace_back(_params.width, false);
                                                                    }
                                                               }


cv::Mat NoOpenCVDetection::getAbsDiff(const cv::Mat &cur_frame) const
{
    cv::Mat diff, sum;
    sum = getMeanSum();
    cv::absdiff(grey::castToGrey(cur_frame), sum, diff);

    return diff;
}

std::vector<cv::Rect> NoOpenCVDetection::findRectangles(const cv::Mat &cur_frame)
{
    cv::Mat diff = getAbsDiff(cur_frame);
    changeSum(cur_frame);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, _dilate_kernel_size);
    cv::dilate(diff, diff, kernel);

    //cv::threshold(diff, diff, _threshold_value, consts::thresholds::MAX_THRESHOLDS, cv::THRESH_BINARY);

    std::vector<cv::Rect> contours;
    findRects(diff, contours);
    // cv::findRects(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

void NoOpenCVDetection::findRects(const cv::Mat &frame, std::vector<cv::Rect>& contours)
{
    double max_area = 0.05 * _params.height * _params.width;
    double min_area = 1e-4 * _params.height * _params.width;

    for (int y = 50; y < _params.height; y += 50)
    {
        for (int x = 50; x < _params.width; x += 50)
        {
            if (frame.at<uchar>(y, x) >= _threshold_value)
            {
                if (insideContour(contours, cv::Point(x, y)))
                {
                    continue;
                }

                cv::Rect rect;
                bfs(frame, cv::Point(x, y), rect);
                auto s = rect.width * rect.height;
                if (s > min_area && s < max_area)
                {
                    contours.push_back(rect);
                }
            }
        }
    }
}

void NoOpenCVDetection::bfs(const cv::Mat& frame, const cv::Point& point, cv::Rect& rect)
{
    rect = cv::Rect(point, point);
    const int step = 50;

    cv::Point min_point = {(-point.x + step - 1) / step, (-point.y + step - 1) / step};
    cv::Point max_point = {(_params.width - point.x - 1) / step, (_params.height - point.y - 1) / step};

    std::vector<std::vector<bool>> visited(max_point.y - min_point.y + 1,
                                           std::vector<bool>(max_point.x - min_point.x + 1));

    int height = static_cast<int>(visited.size());
    int width = static_cast<int>(visited[0].size());

    std::queue<cv::Point> q;

    cv::Point new_point(point.x / step - min_point.x, point.y / step - min_point.y);
    visited[new_point.y][new_point.x] = true;
    q.push(new_point);

    int offset_x = point.x % step;
    int offset_y = point.y % step;

    while (!q.empty())
    {
        new_point = q.front();
        q.pop();

        cv::Point real_point(offset_x + new_point.x * step, offset_y + new_point.y * step);
        if (frame.at<uchar>(real_point) < _threshold_value)
        {
            continue;
        }

        if (real_point.x < rect.x)
        {
            rect.x = real_point.x;
        }
        if (real_point.y < rect.y)
        {
            rect.y = real_point.y;
        }
        if (real_point.x > rect.x + rect.width)
        {
            rect.width = real_point.x - rect.x;
        }
        if (real_point.y > rect.y + rect.height)
        {
            rect.height = real_point.y - rect.y;
        }


        // TODO вынести в константу
        for (size_t i = 0; i < 4; ++i)
        {
            // TODO check this think about var new_point
            auto p(cv::Point(point.x + consts::moore::dx[i], point.y + consts::moore::dy[i]));

            if (p.x >= 0 && p.y >= 0 && p.y < height && p.x < width && !visited[p.y][p.x])
            {
                visited[p.y][p.x] = true;
                q.push(p);
            }
        }
    }
}

cv::Mat NoOpenCVDetection::gaussianFilter(const cv::Mat &in_frame)
{
    // auto out_frame = grey::castToGrey(_blur.gaussianBlur(in_frame));

    cv::Mat zxc = in_frame.clone();
    cv::GaussianBlur(in_frame, zxc, _blur_kernel_size, 0, 0);
    cv::cvtColor(zxc, zxc, cv::COLOR_BGR2GRAY);

    //cv::imshow("Frame", out_frame);
    //cv::imshow("zxc", zxc);
    //cv::waitKey();

    return zxc;
}

std::map<size_t, cv::Rect> NoOpenCVDetection::detectMotion(cv::Mat &cur_frame) {
    if (_frames.size() != _capacity)
    {
        addFrames(cur_frame);
        return {};
    }

    std::vector<cv::Rect> rectangles = findRectangles(cur_frame);

    deleteInnerRectangles(rectangles);
    findPermanentRectangles(rectangles);

    for (const auto& rect : rectangles)
    {
        cv::rectangle(cur_frame, rect, consts::color_map.at(RED), consts::thickness::MEDIUM, cv::LINE_8);
    }

    std::map<size_t, cv::Rect> result;
    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        if (std::get<0>(_rectangles_center[i]) >= _patience)
        {
            result[i] = _rectangles[i];
        }
    }

    return result;
}

bool NoOpenCVDetection::insideContour(const std::vector<cv::Rect> &contours, const cv::Point& point) {
    return std::any_of(contours.begin(), contours.end(), [&point](const cv::Rect& rect)
    {
        return geom::isInnerPoint(point, rect);
    });
}
