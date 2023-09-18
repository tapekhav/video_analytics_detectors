#ifndef VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H
#define VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H

#include <opencv4/opencv2/opencv.hpp>


/*!
 * \class VideoWriter
 * \brief A class for writing video frames to a video file.
 * The VideoWriter class provides functionality for writing video frames to an output video file.
 */
class VideoWriter
{
public:
    //! Constructor
    VideoWriter(const std::string& file_name, int frame_width, int frame_height, double fps);

    //! Write a video frame to the output video.
    void writeVideo(const cv::Mat& frame) { _video_writer.write(frame); }

    //! Destructor
    ~VideoWriter() { _video_writer.release(); }
private:
    cv::VideoWriter _video_writer;
};

#endif //VIDEO_ANALYTICS_DETECTORS_VIDEO_WRITING_H
