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

namespace Constants
{
    enum Thickness
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

    struct Thresholds
    {
        static const int MAX_THRESHOLDS = 255;
        static const int THRESHOLD_VALUE = 50;
    };

    struct Memory
    {
        static const size_t TRAJECTORY_MEMORY = 30;
        static const size_t MOTION_DETECTION_MEMORY = 15;
    };

    struct ExtendedRectangle
    {
        static const int k_max_deviation = 30;
        static const int k_patience = 8;
        static const int k_max_elapsed_time = 3;
    };
}

#endif //VIDEO_ANALYTICS_DETECTORS_CONSTANTS_H
