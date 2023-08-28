#include <object_tracking.h>

void ObjectTracking::OneRectangleTrajectory(size_t id, const cv::Rect& rectangle, cv::Mat& frame)
{
    auto last_point = Geometry::findCenter(rectangle);

    cv::Scalar turquoise_color(255, 255, 0);
    cv::line(frame, _history[id].front(), last_point, turquoise_color, Constants::Thickness::THICK, cv::LineTypes::LINE_8);

    _history[id].push(last_point);
    if (_history[id].size() >= _memory)
    {
        _history[id].pop();
    }
}
