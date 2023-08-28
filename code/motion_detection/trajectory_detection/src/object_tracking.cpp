#include <object_tracking.h>

void ObjectTracking::OneRectangleTrajectory(size_t id, const cv::Rect& rectangle, cv::Mat& frame)
{
    auto last_point = Geometry::findCenter(rectangle);

    cv::Scalar blue_color(255, 255, 0);
    cv::line(frame, _history[id].front(), last_point, blue_color, );

    _history[id].push(last_point);
    if (_history[id].size() >= _memory)
    {
        _history[id].pop();
    }
}
