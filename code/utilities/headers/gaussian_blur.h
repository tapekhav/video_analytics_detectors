#ifndef VIDEO_ANALYTICS_DETECTORS_GAUSSIAN_BLUR_H
#define VIDEO_ANALYTICS_DETECTORS_GAUSSIAN_BLUR_H

#include <utility>
#include <cassert>
#include <cstddef>
#include <opencv4/opencv2/opencv.hpp>


/*!
 * \class GaussianBlur
 * \brief A class for applying Gaussian blur to images.
 * The GaussianBlur class provides functionality to apply Gaussian blur to an input image using
 * a specified kernel size and sigma value.
 */
class GaussianBlur
{
public:
    //! Constructor
    GaussianBlur(int k_size, double sigma) : _kernel_size(k_size), _sigma(sigma) { assert(_kernel_size % 2 == 1); }
    //! Apply Gaussian blur to an input image.
    cv::Mat gaussianBlur(const cv::Mat& in_frame);
private:
    //! Generate a Gaussian kernel.
    [[nodiscard]] std::vector<std::vector<double>> gaussianKernel() const;

private:
    int _kernel_size;
    double _sigma;
};

#endif //VIDEO_ANALYTICS_DETECTORS_GAUSSIAN_BLUR_H
