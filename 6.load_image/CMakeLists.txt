cmake_minimum_required(VERSION 2.8)

project(load)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_load load.cpp)

target_link_libraries(cv_load ${OpenCV_LIBS})
