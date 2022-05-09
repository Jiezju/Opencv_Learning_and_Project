cmake_minimum_required(VERSION 3.20)
project(15_floodFill)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(17_thresh
        17_thresh.cpp)

target_link_libraries(17_thresh ${OpenCV_LIBS})