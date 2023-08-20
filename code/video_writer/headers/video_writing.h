#ifndef VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H
#define VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H

#include <opencv4/opencv2/opencv.hpp>

class VideoWriter
{
public:
    VideoWriter(const std::string& file_name, int frame_width, int frame_height, double fps);

    void writeVideo(const std::vector<cv::Mat>& frames);

    ~VideoWriter() { _writer.release(); }
private:
    cv::VideoWriter _writer;
};

#endif //VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H
