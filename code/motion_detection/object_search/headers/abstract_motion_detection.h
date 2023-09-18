#ifndef VIDEO_ANALYTICS_DETECTORS_ABSTRACT_MOTION_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_ABSTRACT_MOTION_DETECTION_H

#include <deque>
#include <utility>
#include <cmath>

#include <geometry.h>
#include <constants.h>

/*!
 * \class AbstractMotionDetection
 * \brief A base class for motion detection algorithms.
 *
 * This class provides a framework for implementing various motion detection algorithms for video analytics.
 * Subclasses can override the virtual methods to implement specific detection logic.
 */
class AbstractMotionDetection
{
public:
    //! Method for detection motion objects
    std::map<size_t, cv::Rect> detectMotion(cv::Mat& cur_frame);
    //! Destructor
    virtual ~AbstractMotionDetection() = default;
protected:
    /*!
     * Constructor for the AbstractMotionDetection class.
     * \param params The size of parameters used in the detection algorithm.
     * \param threshold The threshold value for motion detection.
     * \param dilate_kernel_size The size of the kernel used for dilating detected regions.
     * \param frames The number of frames to consider for motion detection.
     * \param blur_kernel_size The size of the kernel used for blurring frames.
     * \param max_deviation The maximum deviation allowed for motion detection.
     * \param patience The patience level for motion detection.
     * \param max_elapsed_time The maximum elapsed time for motion detection.
     */
    AbstractMotionDetection(cv::Size params,
                            int threshold,
                            cv::Size dilate_kernel_size,
                            size_t frames,
                            cv::Size blur_kernel_size,
                            int max_deviation,
                            int patience,
                            int max_elapsed_time);

    //! Deletes inner rectangles
    void deleteInnerRectangles(std::vector<cv::Rect> &rectangles);
    //! Finding only permanent rectangles using patience, max_elapsed_time
    void findPermanentRectangles(std::vector<cv::Rect> &rectangles);
    //! Need for add new frame
    void addFrames(const cv::Mat& frame);
    //! Need for background subtraction
    void changeSum(const cv::Mat &frame);
    //! Need for sum first 20 frames
    bool addFirstFrames(const cv::Mat& frame);
    //! Finds mean sum, need for background substraction
    [[nodiscard]] cv::Mat getMeanSum() const;
    //! Gaussian filter for noise smoothing
    virtual cv::Mat gaussianFilter(const cv::Mat& in_frame) = 0;
    //! Finds all moving objects and displays them as a rectangle
    virtual std::vector<cv::Rect> findRectangles(const cv::Mat& frame) = 0;
    //! Draw rectangle in frame
    void drawRectangles(const cv::Mat& frame, const std::vector<cv::Rect>& rectangles);
    //! Returns all rectangles
    std::map<size_t, cv::Rect> getResult(const std::vector<cv::Rect>& rectangles);
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
