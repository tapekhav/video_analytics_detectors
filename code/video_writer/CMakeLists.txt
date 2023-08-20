cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)
include_directories(headers)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB WRITER_HEADERS headers/*.h)
file(GLOB WRITER_SOURCE src/*.cpp)

add_library(VideoWriter ${WRITER_HEADERS} ${WRITER_SOURCE})
target_link_libraries(VideoWriter ${OpenCV_LIBS})