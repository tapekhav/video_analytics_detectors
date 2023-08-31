#include <object_tracking.h>

void ObjectTracking::oneRectangleTrajectory(cv::Mat& frame, size_t id, const cv::Rect& rectangle)
{
    for (size_t i = 0; i < _history[id].size() - 1; ++i)
    {
        cv::line(frame, _history[id][i], _history[id][i + 1], Constants::color_map.at(Color::TURQUOISE),
                                                              Constants::Thickness::THICK);

    }
    _history[id].push_back(geom::findCenter(rectangle));
}

void ObjectTracking::writeTrajectory(cv::Mat &frame, const std::map<size_t, cv::Rect>& rectangles)
{
    for (const auto& rect : rectangles)
    {
        _history[rect.first].push_back(geom::findCenter(rect.second));
    }

    for (const auto& rect : rectangles)
    {
        oneRectangleTrajectory(frame, rect.first, rect.second);
    }
}
