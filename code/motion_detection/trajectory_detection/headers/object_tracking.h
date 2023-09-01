#ifndef VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
#define VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H

#include <map>

#include <geometry.h>
#include <constants.h>

using rectangle_points = std::map<size_t, std::vector<cv::Point>>;

class ObjectTracking
{
public:
    explicit ObjectTracking(size_t memory = Constants::Memory::TRAJECTORY_MEMORY) : _memory(memory) {}

    void writeTrajectory(cv::Mat& frame, const std::map<size_t, cv::Rect>& rectangles);

private:
    void oneRectangleTrajectory(cv::Mat& frame, size_t id, const cv::Rect& rectangle);

private:
    rectangle_points _history;
    const size_t _memory;

    std::map<size_t, size_t> _frame_counter;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
