#ifndef VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
#define VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H

#include <vector>
#include <opencv4/opencv2/opencv.hpp>


//!TODO Put it in another file
//!TODO add colors to Constants
namespace Constants
{
    enum Thickness
    {
        THIN = 1,
        MEDIUM = 4,
        THICK = 8
    };

    struct Thresholds
    {
        static const int MAX_THRESHOLDS = 255;
        static const int THRESHOLD_VALUE = 43;
    };

    struct Memory
    {
        static const size_t TRAJECTORY_MEMORY = 30;
        static const size_t MOTION_DETECTION_MEMORY = 15;
    };
}

namespace Geometry
{
    void mergeContours(std::vector<cv::Point> &first, const std::vector<cv::Point> &second);

    double checkDistContours(const std::vector<cv::Point> &first, const std::vector<cv::Point> &second);

    bool isInnerRectangle(const cv::Rect &first, const cv::Rect &second);

    inline bool isInnerPoint(const cv::Point &point, const cv::Rect &rect) { return point.inside(rect); }

    double calculateDistance(const cv::Point &p1, const cv::Point &p2);

    inline cv::Point findCenter(const cv::Rect& rect) { return {rect.x + rect.width / 2, rect.y + rect.height}; }
}

#endif //VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
