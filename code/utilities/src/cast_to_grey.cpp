#include <cast_to_grey.h>


cv::Mat grey::castToGrey(const cv::Mat& frame)
{
    auto out = cv::Mat(frame.size(), CV_8UC1);

    for (int i = 0; i < frame.rows; ++i)
    {
        for (int j = 0; j < frame.cols; ++j)
        {
            auto pixel = frame.at<cv::Vec3b>(i, j);
            out.at<uchar>(i, j) = static_cast<uchar>(castPixel(pixel[0], pixel[1], pixel[2]));
        }
    }

    return out;
}
