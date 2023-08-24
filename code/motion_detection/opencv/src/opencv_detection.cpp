#include <opencv_detection.h>

static const int k_thickness = 2;
static const int k_max_threshold_value = 255;

void OpenCVDetection::detectMotion(cv::Mat& cur_frame) {
    if (_frames.size() > _capacity)
    {
        addFrames(cur_frame);
        return;
    }

    cv::Mat diff = getAbsDiff(cur_frame);

    changeSum(cur_frame);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::dilate(diff, diff, kernel);

    cv::GaussianBlur(diff, diff, cv::Size(7, 7), 0, 0);

    cv::threshold(diff, diff, _threshold_value, k_max_threshold_value, cv::THRESH_BINARY);

    // cv::morphologyEx(diff, diff, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    // cv::morphologyEx(diff, diff, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Scalar red_color(0, 0, 255);

    double background_area_threshold = 0.1 * _params.height * _params.width;
    double background_min_area = 2e-5 * _params.height * _params.width;

    for (const auto& contour : contours)
    {
        // std::cout << contour << "\n";
        double area = cv::contourArea(contour);

        if (area < background_area_threshold && area > background_min_area)
        {
            cv::Rect bound_rect = cv::boundingRect(contour);
            cv::rectangle(cur_frame, bound_rect, red_color, k_thickness, cv::LINE_8);
        }
    }
}

cv::Mat OpenCVDetection::getAbsDiff(const cv::Mat &cur_frame)
{
    cv::Mat diff;

    cv::absdiff(cur_frame, _sum_frames / static_cast<double>(_capacity), diff);
    cv::cvtColor(diff, diff, cv::COLOR_BGR2GRAY);

    return diff;
}

void OpenCVDetection::addFrames(const cv::Mat& cur_frame)
{
    cv::add(_sum_frames, cur_frame, _sum_frames);
    _frames.push_back(cur_frame);
}

void OpenCVDetection::changeSum(const cv::Mat &cur_frame)
{
    addFrames(cur_frame);

    _sum_frames -= _frames.front();
    _frames.pop_front();
}
