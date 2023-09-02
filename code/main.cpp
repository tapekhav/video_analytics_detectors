#include <video_capture.h>
#include <video_writing.h>
#include <object_tracking.h>
#include "opencv_detection.h"


int main()
{
    std::string input(VIDEOS_DIR);
    input += "ahah.avi";

    VideoCapture<const std::string> zxc(input);
    auto zv = zxc.displayOriginal();

    std::string output(OUTPUT_DIR);
    output += "output.avi";

    std::unique_ptr<AbstractMotionDetection> aaaa = std::make_unique<OpenCVDetection>(cv::Size(zxc.getFrameWidth(), zxc.getFrameHeight()));
    ObjectTracking z;
    for (auto & frame : zv)
    {
        auto arr = aaaa->detectMotion(frame);
        z.writeTrajectory(frame, arr);
    }

    VideoWriter abc(output, zxc.getFrameWidth(), zxc.getFrameHeight(), zxc.getFPS());
    abc.writeVideo(zv);
}