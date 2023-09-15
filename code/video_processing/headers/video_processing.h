#ifndef VIDEO_ANALYTICS_DETECTORS_VIDEO_PROCESSING_H
#define VIDEO_ANALYTICS_DETECTORS_VIDEO_PROCESSING_H

#include <video_writing.h>
#include <video_capture.h>
#include <abstract_motion_detection.h>
#include <object_tracking.h>

using Capture = VideoCapture<std::string>;

class VideoProcessing
{
public:
    VideoProcessing() : _input_name(VIDEOS_DIR), _output_name(OUTPUT_DIR) {}

    inline void setInputName(const std::string& input_name) { _input_name += input_name; }
    inline void setOutputName(const std::string& output_name) { _output_name += output_name; }

    void process();

private:
    void init();

private:
    std::string _input_name;
    std::string _output_name;
    std::unique_ptr<Capture> _capture;
    std::unique_ptr<VideoWriter> _writer;
    std::unique_ptr<ObjectTracking> _tracking;
    std::unique_ptr<AbstractMotionDetection> _detection;
};

#endif //VIDEO_ANALYTICS_DETECTORS_VIDEO_PROCESSING_H
