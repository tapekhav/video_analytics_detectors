#ifndef VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H

#include <gaussian_blur.h>
#include <abstract_motion_detection.h>

class NoOpenCVDetection final : public AbstractMotionDetection
{
public:
    explicit NoOpenCVDetection(cv::Size params,
                               int threshold = consts::thresholds::THRESHOLD_VALUE,
                               cv::Size dilate_kernel_size = {5, 5},
                               size_t frames = consts::mem::MOTION_DETECTION_MEMORY,
                               cv::Size blur_kernel_size = {9, 9},
                               int max_deviation = consts::ext_rect::k_max_deviation,
                               int patience = consts::ext_rect::k_patience,
                               int max_elapsed_time = consts::ext_rect::k_max_elapsed_time,
                               int my_kernel_size = 5);

    ~NoOpenCVDetection() final = default; 
private:
    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;   

    std::vector<std::vector<cv::Point>> findContours(const cv::Mat &cur_frame) final;

    cv::Mat gaussianFilter(const cv::Mat &in_frame) final;

    double findArea(const std::vector<cv::Point> &contour) final;

    cv::Rect boundContour(const std::vector<cv::Point> &contour) final;

    void bfs(const cv::Mat& frame, const cv::Point& point, std::vector<cv::Point>& contour);

    void findContours(const cv::Mat& frame, std::vector<std::vector<cv::Point>>& contours);

private:
    GaussianBlur _blur;

    std::vector<std::vector<bool>> _visited;
};

#endif //VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
