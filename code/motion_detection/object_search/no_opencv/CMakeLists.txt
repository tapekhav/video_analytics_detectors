cmake_minimum_required(VERSION 3.22.1)

include_directories(headers)
include_directories(../header)

file(GLOB NO_OPENCV_HEADERS headers/*.h)
file(GLOB NO_OPENCV_SOURCE src/*.cpp)

add_library(NoOpencv
            ../header/abstract_motion_detection.h
            ../abstract_motion_detection.cpp
            ${OPENCV_HEADERS}
            ${OPENCV_SOURCE})