cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)
include_directories(headers)
include_directories(../../utilities/headers)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB OPENCV_HEADERS headers/*.h)
file(GLOB OPENCV_SOURCE src/*.cpp)

add_library(Opencv ${OPENCV_HEADERS} ${OPENCV_SOURCE})
target_link_libraries(Opencv ${OpenCV_LIBS})