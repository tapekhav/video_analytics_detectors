#include <opencv_detection.h>

static const int k_thickness = 2;
static const int k_max_threshold_value = 255;

void OpenCVDetection::detectMotion(cv::Mat& cur_frame, const cv::Mat& prev_frame) const
{
    cv::Mat diff;
    cv::absdiff(cur_frame, prev_frame, diff);

    cv::Mat gray_frame;
    cv::cvtColor(diff, gray_frame, cv::COLOR_BGR2GRAY);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
    cv::dilate(diff, diff, kernel);

    cv::GaussianBlur(gray_frame, gray_frame, cv::Size(7, 7), 0, 0);

    cv::threshold(gray_frame, gray_frame, _threshold_value, k_max_threshold_value, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(gray_frame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Scalar red_color(0, 0, 255);
    cv::drawContours(gray_frame, contours, -1, red_color, 1, cv::LINE_8);

    double background_area_threshold = 0.1 * _params.height * _params.width;
    double background_min_area = 2e-5 * _params.height * _params.width;

    for (const auto& contour : contours)
    {
        double area = cv::contourArea(contour);

        if (area < background_area_threshold && area > background_min_area)
        {
            cv::Rect bound_rect = cv::boundingRect(contour);
            cv::rectangle(cur_frame, bound_rect, red_color, k_thickness, cv::LINE_8);
        }
    }

}
