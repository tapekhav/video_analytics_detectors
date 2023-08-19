#ifndef VIDEO_ANALYTICS_DETECTORS_READ_VIDEO_FROM_FILE_H
#define VIDEO_ANALYTICS_DETECTORS_READ_VIDEO_FROM_FILE_H

#include <abstract_video_capture.h>

class VideoCaptureFromFile
{
public:
    explicit VideoCaptureFromFile(const std::string& file_name) : _cam() {}
private:
};

#endif //VIDEO_ANALYTICS_DETECTORS_READ_VIDEO_FROM_FILE_H
