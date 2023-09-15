#include <video_processing.h>
#include <opencv_detection.h>
#include <no_opencv_detection.h>


void VideoProcessing::init()
{
    setInputName("ahah_720.avi");
    setOutputName("output.avi");

    _capture = std::make_unique<Capture>(_input_name);

    auto first_frame = _capture->displayOriginal();
    if (first_frame.empty())
    {
        return;
    }

    _detection = std::make_unique<OpenCVDetection>(cv::Size(_capture->getFrameWidth(), _capture->getFrameHeight()));
    auto rectangles = _detection->detectMotion(first_frame);

    _tracking = std::make_unique<ObjectTracking>(first_frame);
    _tracking->writeTrajectory(first_frame, rectangles);

    _writer = std::make_unique<VideoWriter>(_output_name, _capture->getFrameWidth(), _capture->getFrameHeight(),
                                            _capture->getFPS());
    _writer->writeVideo(first_frame);

    cv::imshow("Cam", first_frame);
}

void VideoProcessing::process()
{
    init();
    for(;;)
    {
        auto frame = _capture->displayOriginal();
        if (frame.empty())
        {
            return;
        }

        auto rects = _detection->detectMotion(frame);
        _tracking->writeTrajectory(frame, rects);

        _writer->writeVideo(frame);
        cv::imshow("Cam", frame);

        char button = static_cast<char>(cv::waitKey(25));
        if (button == 27)
        {
            break;
        }
    }
}
