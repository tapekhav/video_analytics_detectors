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

    for (const auto& p1 : first)
    {
        for (const auto& p2 : second)
        {
            double distance = calculateDistance(p1, p2);
            min_distance = std::min(distance, min_distance);
        }
    }

    return min_distance;
}

double Geometry::calculateDistance(const cv::Point &p1, const cv::Point &p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Geometry::isInnerRectangle(const cv::Rect& first, const cv::Rect& second)
{
    if (isInnerPoint({first.x, first.y}, second) ||
        isInnerPoint({first.x + first.width, first.y}, second) ||
        isInnerPoint({first.x, first.y + first.height}, second) ||
        isInnerPoint({first.x + first.width, first.y + first.height}, second))
    {
        return true;
    }

    return false;
}

