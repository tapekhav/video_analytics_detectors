#include <opencv_detection.h>


OpenCVDetection::OpenCVDetection(cv::Size params,
                                 int threshold,
                                 cv::Size dilate_kernel_size,
                                 size_t _frames,
                                 cv::Size blur_kernel_size,
                                 int max_deviation,
                                 int patience,
                                 int max_elapsed_time)
        : _params(std::move(params)),
          _threshold_value(threshold),
          _dilate_kernel_size(std::move(dilate_kernel_size)),
          _blur_kernel_size(std::move(blur_kernel_size)),
          _sum_frames(cv::Mat::zeros(_params, CV_8UC3)),
          _capacity(_frames),
          _max_deviation(max_deviation),
          _max_elapsed_time(max_elapsed_time),
          _patience(patience),
          _cnt(0) {}

std::vector<cv::Rect> OpenCVDetection::detectMotion(cv::Mat& cur_frame) {
    if (_frames.size() != _capacity)
    {
        addFrames(cur_frame);
        return {};
    }

    std::vector<std::vector<cv::Point>> contours = findContours(cur_frame);

    double background_area_threshold = 0.05 * _params.height * _params.width;
    double background_min_area = 1e-4 * _params.height * _params.width;

    std::vector<cv::Rect> rectangles;
    for (size_t i = 0; i < contours.size() - 1; ++i)
    {
        double area = cv::contourArea(contours[i]);

        if (geom::checkDistContours(contours[i], contours[i + 1]) < background_min_area * 0.2)
        {
            geom::mergeContours(contours[i], contours[i + 1]);
        }

        if (area < background_area_threshold && area > background_min_area)
        {
            cv::Rect bound_rect = cv::boundingRect(contours[i]);
            rectangles.push_back(bound_rect);
        }
    }

    deleteInnerRectangles(rectangles);
    findPermanentRectangles(rectangles);


    for (const auto& rect : rectangles)
    {
        cv::rectangle(cur_frame, rect, Constants::color_map.at(RED), Constants::Thickness::MEDIUM, cv::LINE_8);
    }

    return rectangles;
}

cv::Mat OpenCVDetection::getAbsDiff(const cv::Mat &cur_frame) const
{
    cv::Mat diff, sum;
    sum = getMeanSum();
    cv::absdiff(cur_frame, sum, diff);

    cv::cvtColor(diff, diff, cv::COLOR_BGR2GRAY);

    return diff;
}

void OpenCVDetection::addFrames(const cv::Mat& cur_frame)
{
    cv::Mat frame;
    cv::GaussianBlur(cur_frame, frame, _blur_kernel_size, 0, 0);

    _sum_frames += frame;
    _frames.push_back(frame);
}

void OpenCVDetection::changeSum(const cv::Mat &cur_frame)
{
    addFrames(cur_frame);

    _sum_frames -= _frames.front();
    _frames.pop_front();
}

cv::Mat OpenCVDetection::getMeanSum() const
{
    cv::Mat sum = _frames[0].clone();
    sum /= static_cast<double>(_capacity);
    for (size_t i = 1; i < _capacity; ++i)
    {
        sum += _frames[i] / static_cast<double>(_capacity);
    }

    return sum;
}

void OpenCVDetection::deleteInnerRectangles(std::vector<cv::Rect> &rectangles)
{
    auto sortByArea = [](const cv::Rect& first, const cv::Rect& second)
    {
        return first.width * first.height > second.width * second.height;
    };

    std::sort(rectangles.begin(), rectangles.end(), sortByArea);

    std::vector<bool> mask(rectangles.size(), false);

    for (size_t i = 0; i < rectangles.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < rectangles.size(); ++j)
        {
            if (geom::isInnerRectangle(rectangles[j], rectangles[i]))
            {
                mask[j] = true;
            }
        }
    }

    std::vector<cv::Rect> filteredRectangles;
    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        if (!mask[i])
        {
            filteredRectangles.push_back(rectangles[i]);
        }
    }

    rectangles = filteredRectangles;
}

std::vector<std::vector<cv::Point>> OpenCVDetection::findContours(const cv::Mat &cur_frame)
{
    cv::Mat diff = getAbsDiff(cur_frame);
    changeSum(cur_frame);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, _dilate_kernel_size);
    cv::dilate(diff, diff, kernel);

    cv::threshold(diff, diff, _threshold_value, Constants::Thresholds::MAX_THRESHOLDS, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}


void OpenCVDetection::findPermanentRectangles(std::vector<cv::Rect> &rectangles)
{
    std::vector<bool> used_rectangles(rectangles.size(), false);
    if (_rectangles.empty())
    {
        for (const auto &rectangle : rectangles)
        {
            _rectangles[_cnt] = rectangle;
            _rectangles_center[_cnt++] = {0, 0, true};
        }
        return;
    }

    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        cv::Rect extended_rect = { rectangles[i].x - _max_deviation, rectangles[i].y - _max_deviation,
                                   rectangles[i].width + 2 * _max_deviation, rectangles[i].height + 2 * _max_deviation };
        for (size_t j = 0; j < _rectangles.size(); ++j)
        {
            auto value = _rectangles_center.find(j) == _rectangles_center.end() ? std::tuple<int, int, bool>(0, 0, false)
                                                                                : _rectangles_center[j];
            std::tuple<int, int, bool> center_value = {std::get<0>(value), std::get<1>(value), false};
            if (geom::isInnerPoint(geom::findCenter(rectangles[j]), extended_rect))
            {
                _rectangles[j] = extended_rect;
                used_rectangles[i] = true;

                auto [cnt, time, flag] = _rectangles_center[i];
                std::tuple<int, int, bool> rectangle_center = {cnt + 1, 0, true};
                _rectangles_center[i] = rectangle_center;

                break;
            }
        }
    }

    std::vector<size_t> ids;
    for (auto& rect_center : _rectangles_center)
    {
        auto [cnt, time, is_in_frame] = rect_center.second;
        if (is_in_frame)
        {
            ++time;
            rect_center.second = {cnt, time, is_in_frame};

            if (time >= _max_elapsed_time)
            {
                ids.push_back(rect_center.first);
            }
        }
    }

    for (const auto& id : ids)
    {
        _rectangles.erase(id);
    }

    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        if (used_rectangles[i])
        {
            _rectangles[_cnt] = rectangles[i];
            _rectangles_center[_cnt++] = {0, 0, true};
        }
    }

    std::vector<cv::Rect> result;
    for (size_t i = 0; i < _rectangles.size(); ++i)
    {
        if (std::get<0>(_rectangles_center[i]) >= _patience)
        {
            result.push_back(_rectangles[i]);
        }
    }

    rectangles = result;
}
