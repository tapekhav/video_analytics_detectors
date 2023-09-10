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

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, _dilate_kernel_size);
    cv::dilate(diff, diff, kernel);

    cv::threshold(diff, diff, _threshold_value, consts::thresholds::MAX_THRESHOLDS, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    // findContours(diff, contours);
    cv::findContours(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

void NoOpenCVDetection::findContours(const cv::Mat &frame, std::vector<std::vector<cv::Point>>& contours)
{
    for (int i = 0; i < _params.height; i += 10)
    {
        for (int j = 0; j < _params.width; j += 10)
        {
            if (!_visited[i][j] && frame.at<uchar>(i, j) > _threshold_value)
            {
                std::vector<cv::Point> contour = {cv::Point(0.0, 1.0)};
                cv::Point point(j, i);
                bfs(frame, point, contour);
                contours.push_back(contour);
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
        auto p = queue.front();
        queue.pop();
        _visited[point.y][point.x] = true;

        //! TODO change 4 to const
        for (int i = 0; i < 4; ++i)
        {
            if (point.y + consts::moore::dy[i] < _params.height && point.x + consts::moore::dx[i] < _params.width
            && frame.at<uchar>(point.y + consts::moore::dy[i], point.x + consts::moore::dx[i]) < _threshold_value)
            {
                _visited[point.y][point.x] = true;
                queue.pop();
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
    return cv::contourArea(contour);
}

cv::Rect NoOpenCVDetection::boundContour(const std::vector<cv::Point> &contour)
{
    return cv::boundingRect(contour);
}
