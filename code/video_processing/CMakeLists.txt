cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)
include_directories(headers)
include_directories(../utilities/headers)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(../motion_detection/object_search/headers)
include_directories(../motion_detection/trajectory_detection/headers)

file(GLOB VIDEO_HEADERS headers/*.h)
file(GLOB VIDEO_SOURCE src/*.cpp)

add_library(VideoProcess ${VIDEO_HEADERS} ${VIDEO_SOURCE})
target_link_libraries(VideoProcess ObjectSearch Utility Trajectory ${OpenCV_LIBS})

add_compile_definitions(VIDEOS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../assets/videos/")
add_compile_definitions(OUTPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../assets/output/")