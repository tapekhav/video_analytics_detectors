#ifndef VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
#define VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H

#include <vector>
#include <opencv4/opencv2/opencv.hpp>

class Geometry
{
public:
    static void mergeContours(std::vector<cv::Point>& first, const std::vector<cv::Point>& second);
    static double checkDistContours(const std::vector<cv::Point>& first, const std::vector<cv::Point>& second);

    static bool isInnerRectangle(const cv::Rect& first, const cv::Rect& second);
private:
    static inline bool isInnerPoint(const cv::Point& point, const cv::Rect& rect) { return point.inside(rect); }
    static double calculateDistance(const cv::Point& p1, const cv::Point& p2);
};

#endif //VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
