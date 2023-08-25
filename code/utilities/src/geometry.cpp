#include "../headers/geometry.h"

std::vector<cv::Point> Geometry::mergeContours(std::vector<cv::Point> first, std::vector<cv::Point> second)
{
    std::vector<cv::Point> merged_contour;
    merged_contour.insert(merged_contour.end(), first.begin(), first.end());
    merged_contour.insert(merged_contour.end(), second.begin(), second.end());

    return merged_contour;
}

double Geometry::checkDistContours(const std::vector<cv::Point>& first, const std::vector<cv::Point>& second)
{
    double min_distance = std::numeric_limits<double>::max();

    for (const auto& point : first)
    {
        double distance = cv::pointPolygonTest(second, point, true);
        min_distance = distance < min_distance ? distance : min_distance;
    }
    
    return min_distance;
}
