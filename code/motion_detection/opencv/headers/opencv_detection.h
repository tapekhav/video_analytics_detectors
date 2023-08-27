#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <deque>
#include <utility>
#include <cmath>

#include <opencv4/opencv2/opencv.hpp>

#include <geometry.h>

class OpenCVDetection
{
public:
    explicit OpenCVDetection(cv::Size params = {200, 200},
                             int threshold = 43,
                             cv::Size dilate_kernel_size = {3, 3},
                             size_t _frames = 15,
                             cv::Size blur_kernel_size = {15, 15})
                             : _params(std::move(params)),
                               _threshold_value(threshold),
                               _dilate_kernel_size(std::move(dilate_kernel_size)),
                               _blur_kernel_size(std::move(blur_kernel_size)),
                               _sum_frames(cv::Mat::zeros(_params, CV_8UC3)),
                               _capacity(_frames) {}

    void detectMotion(cv::Mat& cur_frame);
private:
    std::vector<std::vector<cv::Point>> findContours(const cv::Mat& cur_frame);

    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;

    void addFrames(const cv::Mat& cur_frame);

    void changeSum(const cv::Mat& cur_frame);

    void changeRectangles(std::vector<cv::Rect>& rectangles);

    [[nodiscard]] cv::Mat getMeanSum() const;

private:
    cv::Size _params;
    int _threshold_value;

    cv::Size _dilate_kernel_size;
    cv::Size _blur_kernel_size;

    const size_t _capacity;
    cv::Mat _sum_frames;
    std::deque<cv::Mat> _frames;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
