#ifndef VIDEO_ANALYTICS_DETECTORS_CONSTANTS_H
#define VIDEO_ANALYTICS_DETECTORS_CONSTANTS_H

#include <map>

#include <opencv4/opencv2/opencv.hpp>

enum Color
{
    RED,
    GREEN,
    BLUE,
    TURQUOISE
};

namespace consts
{
    enum thickness
    {
        THIN = 1,
        MEDIUM = 4,
        THICK = 8
    };

    static const std::map<Color, cv::Scalar> color_map =
    {
            {RED, cv::Scalar(0, 0, 255)},
            {GREEN, cv::Scalar(0, 255, 0)},
            {BLUE, cv::Scalar(255, 0, 0)},
            {TURQUOISE, cv::Scalar(255, 255, 0)}
    };

    namespace thresholds
    {
        const int MAX_THRESHOLDS = 255;
        const int THRESHOLD_VALUE = 50;
    };

    namespace mem
    {
        const size_t TRAJECTORY_MEMORY = 30;
        const size_t MOTION_DETECTION_MEMORY = 15;
    };

    namespace ext_rect
    {
        const int k_max_deviation = 30;
        const int k_patience = 8;
        const int k_max_elapsed_time = 3;
    };

    namespace moore
    {
        const int dx[] = {0, 0, -1, 1};
        const int dy[] = {1, -1, 0, 0};
    }
}

#endif //VIDEO_ANALYTICS_DETECTORS_CONSTANTS_H
