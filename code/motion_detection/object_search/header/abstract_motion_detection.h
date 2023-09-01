#ifndef VIDEO_ANALYTICS_DETECTORS_ABSTRACT_MOTION_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_ABSTRACT_MOTION_DETECTION_H

#include <deque>
#include <utility>
#include <cmath>

#include <geometry.h>
#include <constants.h>


class AbstractMotionDetection
{
public:

protected:
    // void deleteInnerRectangles(std::vector<cv::Rect> &rectangles);

protected:
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

#endif //VIDEO_ANALYTICS_DETECTORS_ABSTRACT_MOTION_DETECTION_H
