#include <video_capture.h>


int main()
{
    std::string result_dir(VIDEOS_DIR);
    result_dir += "big.avi";
    VideoCapture<const std::string> zxc(result_dir);
    zxc.displayOriginal();
}