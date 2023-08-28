#ifndef VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
#define VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H

#include <geometry.h>
#include <constants.h>

using rectangle_points = std::vector<std::queue<cv::Point>>;

class ObjectTracking
{
public:
    explicit ObjectTracking(size_t memory = Constants::Memory::TRAJECTORY_MEMORY) : _memory(memory) {}

    void writeTrajectory(cv::Mat& frame, const std::vector<cv::Rect>& rectangles);

private:
    void OneRectangleTrajectory(cv::Mat& frame, size_t id, const cv::Rect& rectangle);

private:
    rectangle_points _history;
    const size_t _memory;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
