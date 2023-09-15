#ifndef VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
#define VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H

#include <map>
#include <utility>

#include <geometry.h>
#include <constants.h>

using rectangle_points = std::map<size_t, std::vector<cv::Point>>;

class ObjectTracking
{
public:
    explicit ObjectTracking(cv::Mat prev_frame, size_t memory = consts::mem::k_trajectory_memory)
                            : _memory(memory), _prev_frame(std::move(prev_frame)) {}

    void writeTrajectory(cv::Mat& frame, const std::map<size_t, cv::Rect>& rectangles);
private:
    rectangle_points _history;
    const size_t _memory;

    cv::Mat _prev_frame;

    std::map<size_t, size_t> _frame_counter;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H