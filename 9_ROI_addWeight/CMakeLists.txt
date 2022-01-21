cmake_minimum_required(VERSION 3.20)
project(9_ROI_addWeight)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(OpenCV_DIR /home/bright/opencv/opencv-3.4.10/cmake-build-debug)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(9_ROI_addWeight
        9_ImageBlending.cpp)

target_link_libraries(9_ROI_addWeight ${OpenCV_LIBS})