#include <video_capture.h>
#include <video_writing.h>
#include <opencv_detection.h>

int main()
{
    std::string input(VIDEOS_DIR);
    input += "high.avi";

    VideoCapture<const std::string> zxc(input);
    auto zv = zxc.displayOriginal();

    std::string output(OUTPUT_DIR);
    output += "output.avi";

    OpenCVDetection aaaa;
    for (auto i : zv)
    {
        aaaa.detectMotion(i);
    }

    VideoWriter abc(output, zxc.getFrameWidth(), zxc.getFrameHeight(), zxc.getFPS());
    abc.writeVideo(zv);
}