#include <geometry.h>

void geom::mergeContours(std::vector<cv::Point>& first, const std::vector<cv::Point>& second)
{
    first.insert(first.end(), second.begin(), second.end());
}

double geom::checkDistContours(const std::vector<cv::Point>& first, const std::vector<cv::Point>& second)
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

double geom::calculateDistance(const cv::Point &p1, const cv::Point &p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool geom::isInnerRectangle(const cv::Rect& first, const cv::Rect& second)
{
    return isInnerPoint({first.x, first.y}, second) ||
           isInnerPoint({first.x + first.width, first.y}, second) ||
           isInnerPoint({first.x, first.y + first.height}, second) ||
           isInnerPoint({first.x + first.width, first.y + first.height}, second);
}


double geom::findDistanceRectangles(const cv::Rect& first, const cv::Rect& second)
{
    return cv::norm(findCenter(first) - findCenter(second));
}

void geom::mergeRectangles(cv::Rect& first, const cv::Rect& second)
{
    first.x = std::min(first.x, second.x);
    first.y = std::min(first.y, second.y);
    first.width = std::max(first.x + first.width, second.x + second.width) - first.x;
    first.height = std::max(first.y + first.height, second.y + second.height) - first.y;
}
