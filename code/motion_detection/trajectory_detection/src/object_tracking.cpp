#include <object_tracking.h>

void ObjectTracking::oneRectangleTrajectory(cv::Mat& frame, size_t id, const cv::Rect& rectangle)
{
    for (size_t i = 0; i < _history[id].size() - 1; ++i)
    {
        cv::line(frame, _history[id][i], _history[id][i + 1], Constants::color_map.at(Color::TURQUOISE),
                                                              Constants::Thickness::THICK);
    }
}

void ObjectTracking::writeTrajectory(cv::Mat &frame, const std::map<size_t, cv::Rect>& rectangles)
{
    for (auto& figure : rectangles)
    {
        size_t id = figure.first;
        if (_history.find(id) == _history.end())
        {
            _history[id] = {geom::findCenter(figure.second)};
        }
        else
        {
            _history[id].push_back(geom::findCenter(figure.second));
        }
    }

    std::vector<size_t> to_del;
    for (auto& kv : _history)
    {
        size_t id = kv.first;
        auto& positions = kv.second;
        for (size_t i = 0; i < positions.size() - 1; ++i)
        {
            cv::line(frame, positions[i], positions[i + 1], Constants::color_map.at(Color::TURQUOISE),
                                                            Constants::Thickness::THICK);
        }
        _frame_counter[id] = _frame_counter.find(id) == _frame_counter.end() ? 1 : _frame_counter[id] + 1;

        if (_frame_counter[id] >= _memory) {
            positions.erase(positions.begin());
            if (positions.empty()) {
                to_del.push_back(id);
            }
        }
    }

    for (auto id : to_del) {
        _history.erase(id);
        _frame_counter.erase(id);
    }
}
