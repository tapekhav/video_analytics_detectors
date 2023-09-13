#include <opencv_detection.h>

#include <utility>


OpenCVDetection::OpenCVDetection(cv::Size params,
                                 int threshold,
                                 cv::Size dilate_kernel_size,
                                 size_t frames,
                                 cv::Size blur_kernel_size,
                                 int max_deviation,
                                 int patience,
                                 int max_elapsed_time)
                                 : AbstractMotionDetection(std::move(params),
                                                           threshold, std::move(dilate_kernel_size),
                                                           frames, std::move(blur_kernel_size),
                                                           max_deviation,
                                                           patience,
                                                           max_elapsed_time) {}

cv::Mat OpenCVDetection::getAbsDiff(const cv::Mat &cur_frame) const
{
    cv::Mat diff, out;
    auto sum = getMeanSum();

    cv::cvtColor(cur_frame, out, cv::COLOR_BGR2GRAY);
    cv::absdiff(out, sum, diff);

    return diff;
}

std::vector<std::vector<cv::Point>> OpenCVDetection::findContours(const cv::Mat &cur_frame)
{
    cv::Mat diff = getAbsDiff(cur_frame);
    changeSum(cur_frame);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, _dilate_kernel_size);
    cv::dilate(diff, diff, kernel);

    cv::threshold(diff, diff, _threshold_value, consts::thresholds::k_max_thresholds, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

cv::Mat OpenCVDetection::gaussianFilter(const cv::Mat &in_frame)
{
    auto out_frame = in_frame.clone();
    cv::GaussianBlur(in_frame, out_frame, _blur_kernel_size, 0, 0);
    cv::cvtColor(out_frame, out_frame, cv::COLOR_BGR2GRAY);

    return out_frame;
}

double OpenCVDetection::findArea(const std::vector<cv::Point> &contour)
{
    return cv::contourArea(contour);
}

cv::Rect OpenCVDetection::boundContour(const std::vector<cv::Point> &contour)
{
    return cv::boundingRect(contour);
}

std::map<size_t, cv::Rect> OpenCVDetection::detectMotion(cv::Mat &cur_frame)
{
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
        double area = findArea(contours[i]);

        for (size_t j = i + 1; j < i + 20 && j < contours.size(); ++j)
        {
            if (geom::checkDistContours(contours[i], contours[j]) < 30)
            {
                geom::mergeContours(contours[i], contours[j]);
            }
        }

        if (area < background_area_threshold && area > background_min_area)
        {
            cv::Rect bound_rect = boundContour(contours[i]);
            rectangles.push_back(bound_rect);
        }
    }

    deleteInnerRectangles(rectangles);
    findPermanentRectangles(rectangles);

    for (const auto& rect : rectangles)
    {
        cv::rectangle(cur_frame, rect, consts::color_map.at(RED), consts::thickness::MEDIUM, cv::LINE_8);
    }

    std::map<size_t, cv::Rect> result;
    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        if (std::get<0>(_rectangles_center[i]) >= _patience)
        {
            result[i] = _rectangles[i];
        }
    }

    return result;
}