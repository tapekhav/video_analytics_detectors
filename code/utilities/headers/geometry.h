#ifndef VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
#define VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H

#include <vector>
#include <opencv4/opencv2/opencv.hpp>

namespace geom
{
    //! Merge two contours.
    void mergeContours(std::vector<cv::Point> &first, const std::vector<cv::Point> &second);
    //! Check the minimum Euclidean distance between two contours.
    double checkDistContours(const std::vector<cv::Point> &first, const std::vector<cv::Point> &second);
    //! Check if one rectangle is entirely contained within another.
    bool isInnerRectangle(const cv::Rect &first, const cv::Rect &second);
    //! Check if a point is inside a rectangle.
    inline bool isInnerPoint(const cv::Point &point, const cv::Rect &rect) { return point.inside(rect); }
    //! Calculate the Euclidean distance between two points.
    double calculateDistance(const cv::Point &p1, const cv::Point &p2);
    //! Calculate the Euclidean distance between two rectangles.
    double findDistanceRectangles(const cv::Rect& first, const cv::Rect& second);
    //! Find the center of a rectangle.
    inline cv::Point findCenter(const cv::Rect& rect) { return {rect.x + rect.width / 2, rect.y + rect.height / 2}; }
    //! Merge two rectangles.
    void mergeRectangles(cv::Rect& first, const cv::Rect& second);
}

#endif //VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
