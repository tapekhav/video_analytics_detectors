#ifndef VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H

#include <abstract_motion_detection.h>

class NoOpenCVDetection final : public AbstractMotionDetection
{
public:
    NoOpenCVDetection(cv::Size params,
                      int threshold = Constants::Thresholds::THRESHOLD_VALUE,
                      cv::Size dilate_kernel_size = {5, 5},
                      size_t frames = Constants::Memory::MOTION_DETECTION_MEMORY,
                      cv::Size blur_kernel_size = {9, 9},
                      int max_deviation = Constants::ExtendedRectangle::k_max_deviation,
                      int patience = Constants::ExtendedRectangle::k_patience,
                      int max_elapsed_time = Constants::ExtendedRectangle::k_max_elapsed_time);

private:
    // cv::Mat getAbsDiff(const cv::Mat &cur_frame) const final;                  

};

#endif //VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
