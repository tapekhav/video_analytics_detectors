#include <object_tracking.h>

void ObjectTracking::OneRectangleTrajectory(cv::Mat& frame, size_t id, const cv::Rect& rectangle)
{
    if (_history.empty())
    {
        auto first_point = geom::findCenter(rectangle);
        _history[id].push(first_point);
    }

    auto last_point = geom::findCenter(rectangle);

    cv::line(frame, _history[id].front(), last_point, Constants::color_map.at(TURQUOISE), Constants::Thickness::THICK,
                                                                                          cv::LineTypes::LINE_8);

    _history[id].push(last_point);
    if (_history[id].size() >= _memory)
    {
        _history[id].pop();
    }
}

//! TODO допилить алгоритм трекинга
void ObjectTracking::writeTrajectory(cv::Mat &frame, const std::vector<cv::Rect>& rectangles)
{
    for (const auto& frame_points : _history)
    {
    }
}
