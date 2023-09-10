#include <object_tracking.h>

void ObjectTracking::oneRectangleTrajectory(cv::Mat& frame, size_t id, std::vector<cv::Point>& positions,
                                                                       std::vector<size_t>& to_del)
{
    for (size_t i = 0; i < positions.size() - 1; ++i)
    {
        //! cv::Scalar color((i * 125) % 255, (i * 1111) % 255, (i * 131) % 255);
        cv::circle(frame, positions[i], Constants::Thickness::THICK, Constants::color_map.at(Color::TURQUOISE),
                   cv::FILLED);
    }
    _frame_counter[id] = _frame_counter.find(id) == _frame_counter.end() ? 1 : _frame_counter[id] + 1;

    if (_frame_counter[id] >= _memory)
    {
        positions.erase(positions.begin());
        if (positions.empty())
        {
            to_del.push_back(id);
        }
    }
}

void ObjectTracking::writeTrajectory(cv::Mat &frame, const std::map<size_t, cv::Rect>& rectangles)
{
    for (auto& figure : rectangles)
    {
        _history[figure.first].push_back(geom::findCenter(figure.second));
    }

    std::vector<size_t> to_del;
    for (auto& kv : _history)
    {
        oneRectangleTrajectory(frame, kv.first, kv.second, to_del);
    }

    for (auto id : to_del)
    {
        _history.erase(id);
        _frame_counter.erase(id);
    }
}
