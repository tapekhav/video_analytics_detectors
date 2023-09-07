#ifndef VIDEO_ANALYTICS_DETECTORS_CAST_TO_GREY_H
#define VIDEO_ANALYTICS_DETECTORS_CAST_TO_GREY_H

#include <opencv2/core/mat.hpp>

namespace grey
{
    const auto castPixel = [](uchar blue, uchar green, uchar red) { return 0.2989 * red + 0.5870 * green + 0.1140 * blue; };

    cv::Mat castToGrey(const cv::Mat& frame);
}

#endif //VIDEO_ANALYTICS_DETECTORS_CAST_TO_GREY_H
