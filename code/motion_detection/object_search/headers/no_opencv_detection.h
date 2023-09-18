#ifndef VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H

#include <gaussian_blur.h>
#include <abstract_motion_detection.h>


/**
 * \class NoOpenCVDetection
 * \brief A custom motion detection class that does not rely on OpenCV.
 * The NoOpenCVDetection class implements a motion detection algorithm without using OpenCV's
 * built-in functions.
 */
class NoOpenCVDetection final : public AbstractMotionDetection
{
public:
    /*!
    * \brief Constructor for NoOpenCVDetection.
    * \param my_kernel_size        Size of the kernel for custom gaussian filter.
    * \param step                  Step size to avoid counting every pixel .
    */
    explicit NoOpenCVDetection(cv::Size params,
                               int threshold = consts::thresholds::k_threshold_value - 25,
                               cv::Size dilate_kernel_size = {5, 5},
                               size_t frames = consts::mem::k_motion_detection_memory,
                               cv::Size blur_kernel_size = {9, 9},
                               int max_deviation = consts::ext_rect::k_max_deviation - 10,
                               int patience = consts::ext_rect::k_patience,
                               int max_elapsed_time = consts::ext_rect::k_max_elapsed_time,
                               int my_kernel_size = 5,
                               int step = consts::step::AVERAGE_STEP);
    //! Destructor
    ~NoOpenCVDetection() final = default; 
private:
    //! Compute the absolute difference between the current frame and the mean frame.
    [[nodiscard]] cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;   
    //! Find rectangles in the current frame and with them sime operations.
    std::vector<cv::Rect> findRectangles(const cv::Mat &cur_frame) final;
    //! Apply Gaussian blur to an input frame.
    cv::Mat gaussianFilter(const cv::Mat &in_frame) final;
    //! Perform a breadth-first search to find size of rectangle.
    void bfs(const cv::Mat& frame, const cv::Point& point, cv::Rect& rect);
    //! Merge overlapping rectangles in the vector of rectangles.
    void mergeRectangles(std::vector<cv::Rect>& rectangles);
    //! Find rectangles in the given frame.
    void findRects(const cv::Mat& frame, std::vector<cv::Rect>& rectangles);
private:
    GaussianBlur _blur;
    int _step;
};

#endif //VIDEO_ANALYTICS_DETECTORS_NO_OPENCV_DETECTION_H
