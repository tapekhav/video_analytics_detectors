#include <object_tracking.h>

void ObjectTracking::writeTrajectory(cv::Mat& frame, const std::map<size_t, cv::Rect>& rectangles)
{
    for (auto& figure : rectangles)
    {
        size_t id = figure.first;
        cv::Rect object_box = figure.second;

        std::vector<cv::Point2f> prev_points, curr_points;
        cv::Point2f center = geom::findCenter(object_box);
        prev_points.push_back(center);

        std::vector<uchar> status;
        std::vector<float> err;
        cv::calcOpticalFlowPyrLK(_prev_frame, frame, prev_points, curr_points, status, err);

        if (!status.empty() && status[0] == 1)
        {
            cv::Point2f newCenter = curr_points[0];
            _history[id].push_back(newCenter);

            for (const auto & i : _history[id])
            {
                cv::circle(frame, i, consts::thickness::MEDIUM, consts::color_map.at(Color::TURQUOISE),
                                                                cv::FILLED);
            }
        }

        while (_history[id].size() > _memory)
        {
            _history[id].erase(_history[id].begin());
        }
    }

    _prev_frame = frame.clone();
}

