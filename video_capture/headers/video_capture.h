#ifndef VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
#define VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H

#include <opencv4/opencv2/opencv.hpp>

template <class T=int>
class VideoCapture
{
public:
    explicit VideoCapture(T name=0) : _cam(name) { assert(_cam.isOpened()); }

    std::vector<cv::Mat> displayOriginal();

    ~VideoCapture();
protected:
    cv::VideoCapture _cam;
};

template<class T>
std::vector<cv::Mat> VideoCapture<T>::displayOriginal()
{
    std::vector<cv::Mat> result;

    for(;;)
    {
        cv::Mat frame;
        _cam >> frame;

        if (frame.empty())
        {
            return result;
        }
        result.push_back(frame);

        cv::imshow("Cam", frame);

        char button = static_cast<char>(cv::waitKey(25));
        if (button == 27)
        {
            return result;
        }
    }
}

template<class T>
VideoCapture<T>::~VideoCapture()
{
    _cam.release();
}

#endif //VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
