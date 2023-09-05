#ifndef VIDEO_ANALYTICS_DETECTORS_GAUSSIAN_BLUR_H
#define VIDEO_ANALYTICS_DETECTORS_GAUSSIAN_BLUR_H

#include <utility>
#include <cassert>
#include <cstddef>
#include <opencv4/opencv2/opencv.hpp>

class GaussianBlur
{
public:
    GaussianBlur(int k_size, double sigma) : _kernel_size(k_size), _sigma(sigma) { assert(_kernel_size % 2 == 1); }

    void gaussianBlur(const cv::Mat& in_frame, cv::Mat& frame);
private:
    [[nodiscard]] cv::Mat gaussianKernel() const;

private:
    int _kernel_size;
    double _sigma;
};

#endif //VIDEO_ANALYTICS_DETECTORS_GAUSSIAN_BLUR_H
