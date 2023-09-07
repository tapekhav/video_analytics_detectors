#include <gaussian_blur.h>
#include <constants.h>

std::vector<std::vector<double>> GaussianBlur::gaussianKernel() const
{
    int halfKernelSize = _kernel_size / 2;

    // Generate the Gaussian kernel
    std::vector<std::vector<double>> kernel(_kernel_size, std::vector<double>(_kernel_size, 0.0));
    double kernelSum = 0.0;

    for (int i = -halfKernelSize; i <= halfKernelSize; ++i)
    {
        for (int j = -halfKernelSize; j <= halfKernelSize; ++j)
        {
            double exponent = -(i * i + j * j) / (2 * _sigma * _sigma);
            kernel[i + halfKernelSize][j + halfKernelSize] = exp(exponent) / (2 * M_PI * _sigma * _sigma);
            kernelSum += kernel[i + halfKernelSize][j + halfKernelSize];
        }
    }

    // Normalize the kernel
    for (int i = 0; i < _kernel_size; ++i)
    {
        for (int j = 0; j < _kernel_size; ++j)
        {
            kernel[i][j] /= kernelSum;
        }
    }


    return kernel;
}

cv::Mat GaussianBlur::gaussianBlur(const cv::Mat& in_frame)
{
    auto frame = in_frame.clone();

    auto kernel = gaussianKernel();
    int halfKernelSize = _kernel_size / 2;

    for (int y = 0; y < in_frame.rows; ++y)
    {
        for (int x = 0; x < in_frame.cols; ++x)
        {
            cv::Vec3b sum = {0, 0, 0};
            for (int i = -halfKernelSize; i <= halfKernelSize; ++i)
            {
                for (int j = -halfKernelSize; j <= halfKernelSize; ++j)
                {
                    int shift_y = y + i;
                    int shift_x = x + j;
                    if (shift_y >= 0 && shift_y < in_frame.rows && shift_x >= 0 && shift_x < in_frame.cols)
                    {
                        sum += in_frame.at<cv::Vec3b>(shift_y, shift_x) * kernel[i + halfKernelSize][j + halfKernelSize];
                    }
                }
            }
            frame.at<cv::Vec3b>(y, x) = sum;
        }
    }

    return frame;
}