#ifndef VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
#define VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H

#include <vector>
#include <opencv4/opencv2/opencv.hpp>

class Geometry
{
public:
    static std::vector<cv::Point> mergeContours(std::vector<cv::Point> first, std::vector<cv::Point> second);
    static double checkDistContours(const std::vector<cv::Point>& first, const std::vector<cv::Point>& second);
};

#endif //VIDEO_ANALYTICS_DETECTORS_GEOMETRY_H
