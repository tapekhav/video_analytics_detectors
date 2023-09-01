#ifndef VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
#define VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H

#include <vector>
#include <opencv4/opencv2/opencv.hpp>

namespace geom
{
    void mergeContours(std::vector<cv::Point> &first, const std::vector<cv::Point> &second);

    double checkDistContours(const std::vector<cv::Point> &first, const std::vector<cv::Point> &second);

    bool isInnerRectangle(const cv::Rect &first, const cv::Rect &second);

    inline bool isInnerPoint(const cv::Point &point, const cv::Rect &rect) { return point.inside(rect); }

    double calculateDistance(const cv::Point &p1, const cv::Point &p2);

    inline cv::Point findCenter(const cv::Rect& rect) { return {rect.x + rect.width / 2, rect.y + rect.height / 2}; }
}

#endif //VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
