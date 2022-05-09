cmake_minimum_required(VERSION 3.20)
project(21_remap)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(21_remap
        remap.cpp)

target_link_libraries(21_remap ${OpenCV_LIBS})