#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <abstract_motion_detection.h>


class OpenCVDetection final : public AbstractMotionDetection
{
public:
    explicit OpenCVDetection(cv::Size params,
                             int threshold = Constants::Thresholds::THRESHOLD_VALUE,
                             cv::Size dilate_kernel_size = {5, 5},
                             size_t frames = Constants::Memory::MOTION_DETECTION_MEMORY,
                             cv::Size blur_kernel_size = {9, 9},
                             int max_deviation = Constants::ExtendedRectangle::k_max_deviation,
                             int patience = Constants::ExtendedRectangle::k_patience,
                             int max_elapsed_time = Constants::ExtendedRectangle::k_max_elapsed_time);

    ~OpenCVDetection() final = default;
private:
    std::vector<std::vector<cv::Point>> findContours(const cv::Mat& cur_frame) final;

    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;

    void gaussianFilter(const cv::Mat& in_frame, cv::Mat& out_frame) final;

    double findArea(const std::vector<cv::Point>& contour) final;

    cv::Rect boundContour(const std::vector<cv::Point>& contour) final;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
