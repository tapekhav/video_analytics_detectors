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
                                     int my_kernel_size,
                                     int step)
                                     : AbstractMotionDetection(std::move(params),
                                                               threshold,
                                                               std::move(dilate_kernel_size),
                                                               frames,
                                                               std::move(blur_kernel_size),
                                                               max_deviation,
                                                               patience,
                                                               max_elapsed_time),
                                                               _blur(9, 3.0),
                                                               _step(step)
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

    std::vector<cv::Rect> contours;
    findRects(diff, contours);

    mergeRectangles(contours);

    return contours;
}

void NoOpenCVDetection::findRects(const cv::Mat &frame, std::vector<cv::Rect>& rectangles)
{
    const double min_area = 1e-4 * _params.height * _params.width;
    cv::Rect rect(0, 0, 0, 0);

    for (int y = _step; y < _params.height; y += _step)
    {
        for (int x = _step; x < _params.width; x += _step)
        {
            if (frame.at<uchar>(y, x) >= _threshold_value)
            {
                bfs(frame, cv::Point(x, y), rect);
                if (rect.area() > min_area)
                {
                    rectangles.push_back(rect);
                }
            }
        }
    }
}

void NoOpenCVDetection::bfs(const cv::Mat& frame, const cv::Point& point, cv::Rect& rect)
{
    rect = cv::Rect(point, point);

    cv::Point min_point((-point.x + _step) / _step, (-point.y + _step) / _step);
    cv::Point max_point((_params.width - point.x) / _step, (_params.height - point.y) / _step);


    std::vector<std::vector<bool>> visited((max_point - min_point).y + 2,
                                            std::vector<bool>((max_point - min_point).x + 2, false));

    int height = static_cast<int>(visited.size());
    int width = static_cast<int>(visited[0].size());

    std::queue<cv::Point> q;

    cv::Point new_point(point.x / _step + 1, point.y / _step + 1);
    visited[new_point.y][new_point.x] = true;
    q.push(new_point);

    int offset_x = point.x % _step;
    int offset_y = point.y % _step;

    while (!q.empty())
    {
        new_point = q.front();
        q.pop();


        cv::Point real_point(offset_x + new_point.x * _step, offset_y + new_point.y * _step);
        if (frame.at<uchar>(real_point) < _threshold_value)
        {
            continue;
        }

        rect.x = std::min(rect.x, real_point.x);
        rect.y = std::min(rect.y, real_point.y);
        rect.width = std::max(rect.width, real_point.x - rect.x);
        rect.height = std::max(rect.height, real_point.y - rect.y);

        for (size_t i = 0; i < consts::four_connectivity::size; ++i)
        {
            auto p(cv::Point(point.x + consts::four_connectivity::dx[i], point.y + consts::four_connectivity::dy[i]));

            if (p.x >= 0 && p.y >= 0 && p.y < height && p.x < width && !visited[p.y][p.x])
            {
                visited[p.y][p.x] = true;
                q.push(p);
            }
        }
    }
}

std::map<size_t, cv::Rect> NoOpenCVDetection::detectMotion(cv::Mat &cur_frame)
{
    if(addFirstFrames(cur_frame))
    {
        return {};
    }

    auto rectangles = findRectangles(cur_frame);

    deleteInnerRectangles(rectangles);
    findPermanentRectangles(rectangles);

    drawRectangles(cur_frame, rectangles);

    return getResult(rectangles);
}

cv::Mat NoOpenCVDetection::gaussianFilter(const cv::Mat &in_frame)
{
    return grey::castToGrey(in_frame);
}

bool NoOpenCVDetection::insideContour(const std::vector<cv::Rect> &contours, const cv::Point& point)
{
    return std::any_of(contours.begin(), contours.end(), [&point](const cv::Rect& rect)
    {
        return geom::isInnerPoint(point, rect);
    });
}


void NoOpenCVDetection::mergeRectangles(std::vector<cv::Rect> &rectangles)
{
    auto isShortDistance = [this](const cv::Rect& first, const cv::Rect& second)
    {
        auto min_dist = std::min(first.width / 2 + second.width / 2, first.height / 2 + second.height / 2);

        return geom::findDistanceRectangles(first, second) < min_dist + 2 * _step;
    };

    for (size_t i = 0; i < rectangles.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < rectangles.size(); ++j)
        {
            if (isShortDistance(rectangles[i], rectangles[j]))
            {
                geom::mergeRectangles(rectangles[i], rectangles[j]);
            }
        }
    }
}
