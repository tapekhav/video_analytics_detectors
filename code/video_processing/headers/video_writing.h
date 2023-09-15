#ifndef VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H
#define VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H

#include <opencv4/opencv2/opencv.hpp>

class VideoWriter
{
public:
    VideoWriter(const std::string& file_name, int frame_width, int frame_height, double fps);

    void writeVideo(const cv::Mat& frame) { _video_writer.write(frame); }

    ~VideoWriter() { _video_writer.release(); }
private:
    cv::VideoWriter _video_writer;
};

#endif //VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H
