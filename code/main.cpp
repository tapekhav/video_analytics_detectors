#include <video_capture.h>
#include <video_writing.h>
#include <opencv_detection.h>

int main()
{
    std::string input(VIDEOS_DIR);
    input += "one_more.avi";

    VideoCapture<const std::string> zxc(input);
    auto zv = zxc.displayOriginal();

    std::string output(OUTPUT_DIR);
    output += "output.avi";

    for (size_t i = 1; i < zv.size(); ++i)
    {
        OpenCVDetection aaaa(15, {zxc.getFrameWidth(), zxc.getFrameHeight()});
        aaaa.detectMotion(zv[i], zv[i - 1]);
    }

    VideoWriter abc(output, zxc.getFrameWidth(), zxc.getFrameHeight(), zxc.getFPS());
    abc.writeVideo(zv);
}