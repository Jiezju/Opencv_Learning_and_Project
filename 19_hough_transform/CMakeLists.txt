cmake_minimum_required(VERSION 3.20)
project(19_houghtTransform)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(OpenCV_DIR /Users/gaojie/my_project/opencv-3.4.14/cmake-build-debug)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(19_houghtTransform
        19_houghtTransform.cpp)

target_link_libraries(19_houghtTransform ${OpenCV_LIBS})