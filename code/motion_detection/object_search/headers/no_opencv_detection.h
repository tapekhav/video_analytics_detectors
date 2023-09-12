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

    std::map<size_t, cv::Rect> detectMotion(cv::Mat &cur_frame) final;

    ~NoOpenCVDetection() final = default; 
private:
    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;   

    std::vector<cv::Rect> findRectangles(const cv::Mat &cur_frame);

    cv::Mat gaussianFilter(const cv::Mat &in_frame) final;

    void bfs(const cv::Mat& frame, const cv::Point& point, cv::Rect& rect);

    void findRects(const cv::Mat& frame, std::vector<cv::Rect>& contours);

    bool insideContour(const std::vector<cv::Rect>& contours, const cv::Point& point);
private:
    GaussianBlur _blur;

    std::vector<std::vector<bool>> _visited;
};

#endif //VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
