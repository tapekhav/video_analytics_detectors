#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <opencv4/opencv2/opencv.hpp>

class OpenCVDetection
{
public:
    OpenCVDetection() = default;

    void detectMotion(cv::Mat& frame);
private:
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
