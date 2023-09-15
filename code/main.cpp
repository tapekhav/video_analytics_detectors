#include <video_capture.h>
#include <video_writing.h>
#include <object_tracking.h>
#include <opencv_detection.h>
#include <no_opencv_detection.h>


int main()
{
    std::string input(VIDEOS_DIR);
    input += "ahah_720.avi";

    VideoCapture<const std::string> zxc(input);
    auto zv = zxc.displayOriginal();

    std::string output(OUTPUT_DIR);
    output += "output.avi";

    std::unique_ptr<AbstractMotionDetection> aaaa = std::make_unique<NoOpenCVDetection>(cv::Size(zxc.getFrameWidth(),
                                                                                                 zxc.getFrameHeight()));
    ObjectTracking z;
    for (auto & frame : zv)
    {
        auto arr = aaaa->detectMotion(frame);
        z.writeTrajectory(frame, arr);
    }

    VideoWriter abc(output, zxc.getFrameWidth(), zxc.getFrameHeight(), 15);
    abc.writeVideo(zv);
}