#ifndef VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
#define VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H

#include <opencv4/opencv2/opencv.hpp>

template <class T=int>
class VideoCapture
{
public:
    explicit VideoCapture(T name=0) : _cam(name) { assert(_cam.isOpened()); }

    std::vector<cv::Mat> displayOriginal();

    [[nodiscard]] inline int getFrameWidth() const { return static_cast<int>(_cam.get(cv::CAP_PROP_FRAME_WIDTH)); }
    [[nodiscard]] inline int getFrameHeight() const { return static_cast<int>(_cam.get(cv::CAP_PROP_FRAME_HEIGHT)); }

    [[nodiscard]] inline double getFPS() const { return _cam.get(cv::CAP_PROP_FPS); }

    inline ~VideoCapture() {_cam.release(); }
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


#endif //VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
