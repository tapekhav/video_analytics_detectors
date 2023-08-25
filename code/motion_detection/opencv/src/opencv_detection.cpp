#include <opencv_detection.h>

static const int k_thickness = 4;
static const int k_max_threshold_value = 255;

void OpenCVDetection::detectMotion(cv::Mat& cur_frame) {
    if (_frames.size() != _capacity)
    {
        std::cout << "+";
        addFrames(cur_frame);
        return;
    }

    cv::Mat diff = getAbsDiff(cur_frame);
    changeSum(cur_frame);

    cv::GaussianBlur(diff, diff, cv::Size(7, 7), 0, 0);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::dilate(diff, diff, kernel);

    cv::threshold(diff, diff, 25, k_max_threshold_value, cv::THRESH_BINARY);

    cv::cvtColor(diff, diff, cv::COLOR_BGR2GRAY);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(diff, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    cv::Scalar red_color(0, 0, 255);

    double background_area_threshold = 0.05 * _params.height * _params.width;
    double background_min_area = 3e-5 * _params.height * _params.width;

    std::vector<cv::Rect> rectangles;
    for (size_t i = 0; i < contours.size(); ++i)
    {
        // std::cout << contour << "\n";
        double area = cv::contourArea(contours[i]);

        // if (Geometry::checkDistContours(contours[i], contours[i + 1]) < 10)
        //{
           //  contours[i] = Geometry::mergeContours(contours[i], contours[i + 1]);
        //}

        if (area < background_area_threshold && area > background_min_area)
        {
            cv::Rect bound_rect = cv::boundingRect(contours[i]);
            rectangles.push_back(bound_rect);
            cv::rectangle(cur_frame, bound_rect, red_color, k_thickness, cv::LINE_8);
        }
    }
    /*
    auto sortByArea = [](const cv::Rect& first, const cv::Rect& second)
    {
        return first.width * first.height > second.height * second.width;
    };

    std::sort(rectangles.begin(), rectangles.end(), sortByArea);



    std::vector<bool> mask(rectangles.size(), false);
    for (size_t i = 0; i < rectangles.size() - 1; ++i)
    {
        if (mask[i])
        {
            continue;
        }

        for (size_t j = i + 1; j < rectangles.size(); ++j)
        {
            mask[j] = Geometry::isInnerRectangle(rectangles[j], rectangles[i]);
        }
    }

    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        if (mask[i])
        {
            rectangles.erase(rectangles.begin() + static_cast<long>(i));
        }
    }
    */
}

cv::Mat OpenCVDetection::getAbsDiff(const cv::Mat &cur_frame)
{
    // cv::namedWindow("sum_frames", cv::WINDOW_NORMAL);
    // cv::imshow("sum_frames", _sum_frames);
    // cv::waitKey(0);


    cv::Mat diff, sum;
    sum = getMeanSum();
    cv::absdiff(cur_frame, sum, diff);

    // cv::namedWindow("diff", cv::WINDOW_NORMAL);
    // cv::imshow("diff", diff);
    // cv::waitKey(0);

    // cv::namedWindow("sum_frames", cv::WINDOW_NORMAL);
    // cv::imshow("sum_frames", sum);
    // cv::waitKey(0);

    return diff;
}

void OpenCVDetection::addFrames(const cv::Mat& cur_frame)
{
    cv::Mat frame;
    cv::GaussianBlur(cur_frame, frame, cv::Size(7, 7), 0, 0);

    _sum_frames += cur_frame;
    _frames.push_back(frame);
}

void OpenCVDetection::changeSum(const cv::Mat &cur_frame)
{
    cv::Mat frame;
    cv::GaussianBlur(cur_frame, frame, cv::Size(7, 7), 0, 0);
    addFrames(frame);

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
