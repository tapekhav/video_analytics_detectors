#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <opencv4/opencv2/opencv.hpp>
#include <utility>

class OpenCVDetection
{
public:
    explicit OpenCVDetection(int threshold = 15,
                             cv::Size params = {200, 200})
                             : _threshold_value(threshold), _params(std::move(params)) {}

    void detectMotion(cv::Mat& cur_frame, const cv::Mat& prev_frame) const;
private:
    int _threshold_value;
    cv::Size _params;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
