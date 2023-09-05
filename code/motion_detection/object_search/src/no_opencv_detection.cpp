#include <no_opencv_detection.h>

NoOpenCVDetection::NoOpenCVDetection(cv::Size params,
                                     int threshold,
                                     cv::Size dilate_kernel_size,
                                     size_t frames,
                                     cv::Size blur_kernel_size,
                                     int max_deviation,
                                     int patience,
                                     int max_elapsed_time)
                                     : AbstractMotionDetection(std::move(params),
                                                               threshold, 
                                                               std::move(dilate_kernel_size),
                                                               frames,
                                                               std::move(blur_kernel_size),
                                                               max_deviation,
                                                               patience,
                                                               max_elapsed_time) {}


