cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)

include_directories(headers)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB UTILITY_HEADERS headers/*.h)
file(GLOB UTILITY_SOURCE src/*.cpp)

add_library(Utility ${UTILITY_HEADERS} ${UTILITY_SOURCE})
target_link_libraries(Utility ${OpenCV_LIBS})