#ifndef VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
#define VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H

#include <deque>
#include <utility>
#include <cmath>

#include <opencv4/opencv2/opencv.hpp>

#include <geometry.h>

class OpenCVDetection
{
public:
    explicit OpenCVDetection(int threshold = 115,
                             cv::Size params = {200, 200})
                             : _threshold_value(threshold),
                               _params(std::move(params)),
                               _sum_frames(cv::Mat::zeros(_params, CV_8UC3)),
                               _capacity(10) {}

    void detectMotion(cv::Mat& cur_frame);

    cv::Mat getAbsDiff(const cv::Mat& cur_frame) const;

    void addFrames(const cv::Mat& cur_frame);

    void changeSum(const cv::Mat& cur_frame);

    cv::Mat getMeanSum() const;
private:
    int _threshold_value;
    cv::Size _params;

    const size_t _capacity;
    cv::Mat _sum_frames;
    std::deque<cv::Mat> _frames;
};

#endif //VIDEO_ANALYTICS_DETECTORS_OPENCV_DETECTION_H
