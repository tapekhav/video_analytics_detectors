#include <gaussian_blur.h>

cv::Mat GaussianBlur::gaussianKernel() const
{
    cv::Mat kernel(_kernel_size, 1, CV_64F);
    double sum = 0.0;

    for (int x = 0; x < _kernel_size; ++x)
    {
        int x_val = x - (_kernel_size - 1) / 2;
        double value = (1 / (2 * CV_PI * _sigma * _sigma)) * std::exp(-((x_val * x_val) / (2 * _sigma * _sigma)));
        kernel.at<double>(x, 0) = value;
        sum += value;
    }

    return kernel / sum;
}

void GaussianBlur::gaussianBlur(cv::Mat &frame)
{
    cv::Mat kernel = gaussianKernel();
    cv::Mat temp_image = frame.clone();

    int pad = _kernel_size / 2;
    int width = frame.cols;
    int height = frame.rows;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double sum = 0.0;
            for (int k = -pad; k <= pad; ++k)
            {
                int idx = x + k;
                if (idx >= 0 && idx < width)
                {
                    sum += temp_image.at<uchar>(y, idx) * kernel.at<double>(k + pad, 0);
                }
            }
            frame.at<uchar>(y, x) = static_cast<uchar>(sum);
        }
    }

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            double sum = 0.0;
            for (int k = -pad; k <= pad; ++k)
            {
                int idx = y + k;
                if (idx >= 0 && idx < height)
                {
                    sum += frame.at<uchar>(idx, x) * kernel.at<double>(k + pad, 0);
                }
            }
            frame.at<uchar>(y, x) = static_cast<uchar>(sum);
        }
    }
}
