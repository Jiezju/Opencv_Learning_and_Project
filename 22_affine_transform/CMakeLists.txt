cmake_minimum_required(VERSION 3.20)
project(22_affine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(affine_transform
        affine_transform.cpp)

target_link_libraries(affine_transform ${OpenCV_LIBS})