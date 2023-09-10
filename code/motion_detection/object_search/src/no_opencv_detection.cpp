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

std::vector<std::vector<cv::Point>> NoOpenCVDetection::findContours(const cv::Mat &cur_frame)
{
    cv::Mat diff = getAbsDiff(cur_frame);
    changeSum(cur_frame);

    // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, _dilate_kernel_size);
    // cv::dilate(diff, diff, kernel);

    //cv::threshold(diff, diff, _threshold_value, consts::thresholds::MAX_THRESHOLDS, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    findContours(diff, contours);
    // cv::findContours(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

void NoOpenCVDetection::findContours(const cv::Mat &frame, std::vector<std::vector<cv::Point>>& contours)
{
    for (int i = 50; i < _params.height / 4; i += 50)
    {
        for (int j = 50; j < _params.width / 4; j += 50)
        {
            if (!_visited[i][j] && frame.at<uchar>(j, i) >= _threshold_value)
            {
                std::vector<cv::Point> contour;
                cv::Point point(j, i);
                bfs(frame, point, contour);
                if (!contour.empty())
                {
                    contours.push_back(contour);
                }
            }
        }
    }
}

void NoOpenCVDetection::bfs(const cv::Mat& frame, const cv::Point& point, std::vector<cv::Point>& contour)
{
    std::queue<cv::Point> queue;

    queue.push(point);

    while (!queue.empty())
    {
        cv::Point p(queue.front());
        contour.push_back(p);
        _visited[p.y][p.x] = true;
        queue.pop();

        //! TODO change 4 to const
        for (int i = 0; i < 4; ++i)
        {
            auto point_y = p.y + consts::moore::dy[i];
            auto point_x = p.x + consts::moore::dx[i];
            if (point_y < _params.height && point_y > 0 && point_x < _params.width && point_x > 0
            && frame.at<uchar>(point_y, point_x) >= _threshold_value && !_visited[point_y][point_x])
            {
                _visited[point_y][point_x] = true;
                queue.emplace(point_x, point_y);
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

double NoOpenCVDetection::findArea(const std::vector<cv::Point> &contour)
{
    return contour.empty() ? 0 : cv::contourArea(contour);
}

cv::Rect NoOpenCVDetection::boundContour(const std::vector<cv::Point> &contour)
{
    return contour.empty() ? cv::Rect(0, 0, 0, 0) : cv::boundingRect(contour);
}
