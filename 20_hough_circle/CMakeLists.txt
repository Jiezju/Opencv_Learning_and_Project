cmake_minimum_required(VERSION 3.20)
project(20_houghtCircle)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(20_hough_circle
        hough_circle.cpp)

target_link_libraries(20_hough_circle ${OpenCV_LIBS})