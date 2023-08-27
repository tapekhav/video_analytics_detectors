#ifndef VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
#define VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H

#include <vector>
#include <opencv4/opencv2/opencv.hpp>


namespace Geometry
{
    void mergeContours(std::vector<cv::Point> &first, const std::vector<cv::Point> &second);

    double checkDistContours(const std::vector<cv::Point> &first, const std::vector<cv::Point> &second);

    bool isInnerRectangle(const cv::Rect &first, const cv::Rect &second);

    inline bool isInnerPoint(const cv::Point &point, const cv::Rect &rect) { return point.inside(rect); }

    double calculateDistance(const cv::Point &p1, const cv::Point &p2);
}

#endif //VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
