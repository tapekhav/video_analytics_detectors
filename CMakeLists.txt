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

#if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
 #   add_compile_options(-Wall -Wextra -Werror -Wpedantic -Wconversion -Wformat -Wunused -Wshadow -Wuninitialized -Wsign-compare)
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
 #   add_compile_options(/W4)
#endif()

add_subdirectory(video_capture)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(video_capture/headers)

add_executable(video_analytics_detectors
               main.cpp)

target_link_libraries(video_analytics_detectors VideoCapture ${OpenCV_LIBS})