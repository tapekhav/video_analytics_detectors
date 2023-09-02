#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <deque>
#include <utility>
#include <cmath>

#include <geometry.h>
#include <constants.h>


class OpenCVDetection
{
public:
    explicit OpenCVDetection(cv::Size params,
                             int threshold = Constants::Thresholds::THRESHOLD_VALUE,
                             cv::Size dilate_kernel_size = {5, 5},
                             size_t _frames = Constants::Memory::MOTION_DETECTION_MEMORY,
                             cv::Size blur_kernel_size = {9, 9},
                             int max_deviation = Constants::ExtendedRectangle::k_max_deviation,
                             int patience = Constants::ExtendedRectangle::k_patience,
                             int max_elapsed_time = Constants::ExtendedRectangle::k_max_elapsed_time);

    std::map<size_t, cv::Rect> detectMotion(cv::Mat& cur_frame);

private:
    std::vector<std::vector<cv::Point>> findContours(const cv::Mat& cur_frame);

    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;

    void addFrames(const cv::Mat& cur_frame);

    void changeSum(const cv::Mat& cur_frame);

    void deleteInnerRectangles(std::vector<cv::Rect>& rectangles);

    void findPermanentRectangles(std::vector<cv::Rect>& rectangles);

    [[nodiscard]] cv::Mat getMeanSum() const;

private:
    cv::Size _params;
    int _threshold_value;

    cv::Size _dilate_kernel_size;
    cv::Size _blur_kernel_size;

    size_t _cnt;
    std::map<size_t, cv::Rect> _rectangles;
    std::map<size_t, std::tuple<int, int, bool>> _rectangles_center;

    const int _max_deviation;
    const int _patience;
    const int _max_elapsed_time;

    const size_t _capacity;
    cv::Mat _sum_frames;
    std::deque<cv::Mat> _frames;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
