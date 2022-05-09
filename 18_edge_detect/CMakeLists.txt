cmake_minimum_required(VERSION 3.20)
project(18_EdgeDetect)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(18_edge_detect
        18_edge_detect.cpp)

target_link_libraries(18_edge_detect ${OpenCV_LIBS})