#include <opencv_detection.h>

void OpenCVDetection::detectMotion(cv::Mat& frame)
{
    cv::GaussianBlur(frame, frame, cv::Size(7, 7), 0, 0);
}
