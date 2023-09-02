cmake_minimum_required(VERSION 3.22.1)

find_package(OpenCV REQUIRED)
include_directories(headers)
include_directories(../../utilities/headers)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB OBJECT_SEARCH_HEADERS headers/*.h)
file(GLOB OBJECT_SEARCH_SOURCE src/*.cpp)

add_library(ObjectSearch
            ${OBJECT_SEARCH_HEADERS}
            ${OBJECT_SEARCH_SOURCE})

target_link_libraries(ObjectSearch Utility ${OpenCV_LIBS})