cmake_minimum_required(VERSION 2.8)

project(color_filtering)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_color_filtering color_filtering.cpp)

target_link_libraries(cv_color_filtering ${OpenCV_LIBS})
