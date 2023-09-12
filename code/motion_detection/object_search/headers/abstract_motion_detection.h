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
    virtual std::map<size_t, cv::Rect> detectMotion(cv::Mat& cur_frame) = 0;

    virtual ~AbstractMotionDetection() = default;
protected:
    AbstractMotionDetection(cv::Size params,
                            int threshold,
                            cv::Size dilate_kernel_size,
                            size_t _frames,
                            cv::Size blur_kernel_size,
                            int max_deviation,
                            int patience,
                            int max_elapsed_time);

    void deleteInnerRectangles(std::vector<cv::Rect> &rectangles);

    void findPermanentRectangles(std::vector<cv::Rect> &rectangles);

    void addFrames(const cv::Mat& cur_frame);

    void changeSum(const cv::Mat &cur_frame);

    [[nodiscard]] cv::Mat getMeanSum() const;

    virtual cv::Mat gaussianFilter(const cv::Mat& in_frame) = 0;
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
