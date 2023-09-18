#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <abstract_motion_detection.h>


/*!
 * \class OpenCVDetection
 * \brief A motion detection class that utilizes OpenCV for motion analysis.
 * The OpenCVDetection class implements motion detection and analysis using OpenCV's built-in
 * functionality.
 */
class OpenCVDetection final : public AbstractMotionDetection
{
public:
    //! Constructor
    explicit OpenCVDetection(cv::Size params,
                             int threshold = consts::thresholds::k_threshold_value + 15,
                             cv::Size dilate_kernel_size = {5, 5},
                             size_t frames = consts::mem::k_motion_detection_memory,
                             cv::Size blur_kernel_size = {7, 7},
                             int max_deviation = consts::ext_rect::k_max_deviation,
                             int patience = consts::ext_rect::k_patience,
                             int max_elapsed_time = consts::ext_rect::k_max_elapsed_time);
    //! Destructor
    ~OpenCVDetection() final = default;
private:
    //! Finds contours in the current frame
    std::vector<std::vector<cv::Point>> findContours(const cv::Mat& frame);
    //! Compute the absolute difference between the current frame and the mean frame.
    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& frame) const;
    //! Apply Gaussian blur to an input frame.
    cv::Mat gaussianFilter(const cv::Mat& in_frame) final;
    //! Calculate the area of a contour.
    double findArea(const std::vector<cv::Point>& contour);
    //! Bound rectangle around a contour.
    cv::Rect boundContour(const std::vector<cv::Point>& contour);
    //! Find motion rectangles in the given frame.
    std::vector<cv::Rect> findRectangles(const cv::Mat& frame) final;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
