#ifndef VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
#define VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H

#include <map>

#include <geometry.h>

#include <opencv4/opencv2/opencv.hpp>

using rectangle_points = std::vector<std::queue<cv::Point>>;

class ObjectTracking
{
public:
    explicit ObjectTracking(size_t memory = Constants::Memory::TRAJECTORY_MEMORY) : _memory(memory) {}

private:
    void OneRectangleTrajectory(size_t id, const cv::Rect& rectangle, cv::Mat& frame);
private:
    rectangle_points _history;
    size_t _memory;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
