#ifndef VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
#define VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H

#include <opencv4/opencv2/opencv.hpp>

class AbstractVideoCapture
{
public:
    AbstractVideoCapture() = default;

    std::vector<cv::Mat> displayOriginal();

    ~AbstractVideoCapture();
private:
    cv::VideoCapture _cam;
};

#endif //VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
