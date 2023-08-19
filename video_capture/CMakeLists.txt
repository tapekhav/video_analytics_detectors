cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)
include_directories(headers)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB CAPTURE_HEADERS headers/*.h)
file(GLOB CAPTURE_SOURCE src/*.cpp)

add_library(VideoCapture ${CAPTURE_HEADERS} ${CAPTURE_SOURCE})
target_link_libraries(VideoCapture ${OpenCV_LIBS})