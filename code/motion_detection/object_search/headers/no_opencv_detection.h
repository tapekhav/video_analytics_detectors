#ifndef VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H

#include <gaussian_blur.h>
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
                      int max_elapsed_time = Constants::ExtendedRectangle::k_max_elapsed_time,
                      double my_kernel_size = 5);

    ~NoOpenCVDetection() final = default; 
private:
    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;   

    std::vector<std::vector<cv::Point>> findContours(const cv::Mat &cur_frame) final;

    void gaussianFilter(const cv::Mat &in_frame, cv::Mat &out_frame) final;

    double findArea(const std::vector<cv::Point> &contour) final;

    cv::Rect boundContour(const std::vector<cv::Point> &contour) final;

    void contouring(const cv::Mat& frame, cv::Point prev, cv::Point cur, std::vector<cv::Point>& contour);

private:
    GaussianBlur _blur;

    std::vector<std::vector<bool>> _visited;
    int num_points;
};

#endif //VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
