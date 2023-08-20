#include <video_capture.h>
#include <video_writing.h>

int main()
{
    std::string input(VIDEOS_DIR);
    input += "big.avi";

    VideoCapture<const std::string> zxc(input);
    auto zv = zxc.displayOriginal();

    std::string output(OUTPUT_DIR);
    output += "output.avi";

    VideoWriter abc(output, zxc.getFrameWidth(), zxc.getFrameHeight(), zxc.getFPS());
    abc.writeVideo(zv);
}