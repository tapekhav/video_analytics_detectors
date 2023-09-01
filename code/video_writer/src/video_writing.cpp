#include <video_writing.h>

VideoWriter::VideoWriter(const std::string &file_name, int frame_width, int frame_height, double fps)
                                                    : _writer(file_name, cv::VideoWriter::fourcc('X', '2', '6', '4'),
                                                              fps,
                                                              cv::Size(frame_width, frame_height),
                                                              true) {}

void VideoWriter::writeVideo(const std::vector<cv::Mat>& frames)
{
    for(const auto& frame : frames)
    {
        // cv::imshow("Frame", frame);
        // cv::waitKey();
        _writer.write(frame);
    }
}
