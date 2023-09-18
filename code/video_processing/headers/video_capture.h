#ifndef VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
#define VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H

#include <opencv4/opencv2/opencv.hpp>


/*!
 * \class VideoCapture
 * \brief A templated class for capturing video frames from a source, such as a camera or video file.
 * The VideoCapture class template provides a generic interface for capturing video frames from
 * various sources. It is templated on the type of source identifier (e.g., camera index or file path).
 */
template <class T=int>
class VideoCapture
{
public:
    //! Constructor
    explicit VideoCapture(T name=0) : _cam(name) { assert(_cam.isOpened()); }
    //! Capture and return an original video frame.
    cv::Mat displayOriginal();

    //! Get the width of the video frames.
    [[nodiscard]] inline int getFrameWidth() const { return static_cast<int>(_cam.get(cv::CAP_PROP_FRAME_WIDTH)); }
    //! Get the height of the video frames.
    [[nodiscard]] inline int getFrameHeight() const { return static_cast<int>(_cam.get(cv::CAP_PROP_FRAME_HEIGHT)); }
    //! Get the frames per second (FPS) of the video source.
    [[nodiscard]] inline double getFPS() const { return _cam.get(cv::CAP_PROP_FPS); }

    //! Destructor
    inline ~VideoCapture() { _cam.release(); }
protected:
    cv::VideoCapture _cam;
};

template<class T>
cv::Mat VideoCapture<T>::displayOriginal()
{
    cv::Mat frame;
    _cam >> frame;

    return frame;
}


#endif //VIDEO_ANALYTICS_DETECTORS_ABSTRACTVIDEOCAPTURE_H
