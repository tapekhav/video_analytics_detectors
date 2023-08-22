#include <opencv_detection.h>

static const int k_thickness = 1;
static const int k_max_threshold_value = 255;

void OpenCVDetection::detectMotion(cv::Mat& frame) const
{
    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray_frame, gray_frame, cv::Size(11, 11), 0, 0);

    cv::threshold(gray_frame, gray_frame, _threshold_value, k_max_threshold_value, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(gray_frame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Scalar blue_color(255, 0, 0);
    cv::drawContours(gray_frame, contours, -1, blue_color, k_thickness, cv::LINE_4);

    for (const auto& contour : contours)
    {
        cv::Rect bound_rect = cv::boundingRect(contour);
        cv::rectangle(frame, bound_rect, cv::Scalar(0, 0, 255), k_thickness + 1, cv::LineTypes::LINE_4);
    }
}
