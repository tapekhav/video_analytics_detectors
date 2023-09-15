cmake_minimum_required(VERSION 3.22.1)
project(video_analytics_detectors)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG ("-std=c++17" COMPILER_HAVE_CPP17)
if (COMPILER_HAVE_CPP17)
    message(STATUS "Adding C++17")
    set(CMAKE_CXX_STANDARD 17)
endif(COMPILER_HAVE_CPP17)

if (MSVC_VERSION GREATER_EQUAL "1900")
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_17)
    if (_cpp_17)
        message(STATUS "Adding C++17")
        add_compile_options("/std:c++17")
    endif()
endif()

add_subdirectory(video_processing)
add_subdirectory(motion_detection)
add_subdirectory(utilities)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(video_processing/headers)
include_directories(motion_detection/object_search/headers)
include_directories(utilities/headers)
include_directories(motion_detection/trajectory_detection/headers)

add_executable(video_analytics_detectors
               main.cpp)

target_link_libraries(video_analytics_detectors ObjectSearch VideoProcess Utility Trajectory ${OpenCV_LIBS})

add_compile_definitions(VIDEOS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../assets/videos/")
add_compile_definitions(OUTPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../assets/output/")