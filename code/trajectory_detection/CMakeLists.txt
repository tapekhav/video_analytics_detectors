cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)

include_directories(headers)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB TRAJECTORY_HEADERS headers/*.h)
file(GLOB TRAJECTORY_SOURCE src/*.cpp)

add_library(Trajectory ${TRAJECTORY_HEADERS} ${TRAJECTORY_SOURCE})
target_link_libraries(Trajectory ${OpenCV_LIBS})