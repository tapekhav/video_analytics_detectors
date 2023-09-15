#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <abstract_motion_detection.h>


class OpenCVDetection final : public AbstractMotionDetection
{
public:
    explicit OpenCVDetection(cv::Size params,
                             int threshold = consts::thresholds::k_threshold_value + 15,
                             cv::Size dilate_kernel_size = {5, 5},
                             size_t frames = consts::mem::k_motion_detection_memory,
                             cv::Size blur_kernel_size = {7, 7},
                             int max_deviation = consts::ext_rect::k_max_deviation,
                             int patience = consts::ext_rect::k_patience,
                             int max_elapsed_time = consts::ext_rect::k_max_elapsed_time);

    ~OpenCVDetection() final = default;
private:
    std::vector<std::vector<cv::Point>> findContours(const cv::Mat& cur_frame);

    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;

    cv::Mat gaussianFilter(const cv::Mat& in_frame) final;

    double findArea(const std::vector<cv::Point>& contour);

    cv::Rect boundContour(const std::vector<cv::Point>& contour);

    std::vector<cv::Rect> findRectangles(const cv::Mat& frame) final;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
