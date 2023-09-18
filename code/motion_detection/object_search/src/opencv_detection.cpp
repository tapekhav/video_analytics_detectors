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

cv::Mat OpenCVDetection::getAbsDiff(const cv::Mat &frame) const
{
    cv::Mat diff, out;
    auto sum = getMeanSum();

    cv::cvtColor(frame, out, cv::COLOR_BGR2GRAY);
    cv::absdiff(out, sum, diff);

    return diff;
}

std::vector<std::vector<cv::Point>> OpenCVDetection::findContours(const cv::Mat &frame)
{
    cv::Mat diff = getAbsDiff(frame);
    changeSum(frame);

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

std::vector<cv::Rect> OpenCVDetection::findRectangles(const cv::Mat &frame)
{
    std::vector<std::vector<cv::Point>> contours = findContours(frame);

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

    return rectangles;
}
