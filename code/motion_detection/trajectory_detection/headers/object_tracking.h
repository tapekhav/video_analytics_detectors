#ifndef VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H
#define VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H

#include <map>
#include <utility>

#include <geometry.h>
#include <constants.h>

//! A type alias representing a map of rectangle points associated with object tracking.
using rectangle_points = std::map<size_t, std::vector<cv::Point>>;

/*!
 * \class ObjectTracking
 * \brief A class that facilitates object tracking within video frames.
 * The ObjectTracking class is designed for tracking objects in a sequence of video frames.
 * It maintains a history of rectangle points associated with objects and provides a method
 * to update this history based on detected rectangles in each frame.
 */
class ObjectTracking
{
public:
    /*!
     * Constructor for ObjectTracking.
     *
     * @param prev_frame    The previous frame used as a reference for tracking.
     * @param memory        The maximum memory length for maintaining object trajectories.
     */
    explicit ObjectTracking(cv::Mat prev_frame, size_t memory = consts::mem::k_trajectory_memory)
                            : _memory(memory), _prev_frame(std::move(prev_frame)) {}
    //! Update the object trajectories based on detected rectangles in a frame.
    void writeTrajectory(cv::Mat& frame, const std::map<size_t, cv::Rect>& rectangles);
private:
    rectangle_points _history;
    const size_t _memory;

    cv::Mat _prev_frame;

    std::map<size_t, size_t> _frame_counter;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OBJECT_TRACKING_H