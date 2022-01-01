cmake_minimum_required(VERSION 3.20)
project(3_load_show)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(OpenCV_DIR /home/bright/opencv/opencv-3.4.10/cmake-build-debug)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(3_load_show
        3_LoadShowOutputImage.cpp)

target_link_libraries(3_load_show ${OpenCV_LIBS})