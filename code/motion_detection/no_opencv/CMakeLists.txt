cmake_minimum_required(VERSION 3.22.1)

include_directories(headers)

file(GLOB NO_OPENCV_HEADERS headers/*.h)
file(GLOB NO_OPENCV_SOURCE src/*.cpp)

add_library(NoOpencv ${NO_OPENCV_HEADERS} ${NO_OPENCV_SOURCE})