#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <opencv4/opencv2/opencv.hpp>

class OpenCVDetection
{
public:
    explicit OpenCVDetection(int threshold = 115) : _threshold_value(threshold) {}

    void detectMotion(cv::Mat& frame) const;
private:
    int _threshold_value;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
