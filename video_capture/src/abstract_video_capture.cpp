#include <abstract_video_capture.h>

std::vector<cv::Mat> AbstractVideoCapture::displayOriginal()
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

AbstractVideoCapture::~AbstractVideoCapture()
{
    _cam.release();
    cv::destroyAllWindows();
}