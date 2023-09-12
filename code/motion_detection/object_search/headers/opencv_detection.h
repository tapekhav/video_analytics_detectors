#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <abstract_motion_detection.h>


class OpenCVDetection final : public AbstractMotionDetection
{
public:
    explicit OpenCVDetection(cv::Size params,
                             int threshold = consts::thresholds::THRESHOLD_VALUE,
                             cv::Size dilate_kernel_size = {5, 5},
                             size_t frames = consts::mem::MOTION_DETECTION_MEMORY,
                             cv::Size blur_kernel_size = {9, 9},
                             int max_deviation = consts::ext_rect::k_max_deviation,
                             int patience = consts::ext_rect::k_patience,
                             int max_elapsed_time = consts::ext_rect::k_max_elapsed_time);

    std::map<size_t, cv::Rect> detectMotion(cv::Mat &cur_frame) final;

    ~OpenCVDetection() final = default;
private:
    std::vector<std::vector<cv::Point>> findContours(const cv::Mat& cur_frame);

    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;

    cv::Mat gaussianFilter(const cv::Mat& in_frame) final;

    double findArea(const std::vector<cv::Point>& contour);

    cv::Rect boundContour(const std::vector<cv::Point>& contour);
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
