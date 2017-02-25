cmake_minimum_required(VERSION 2.8)

project(edge)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_edge edge.cpp)

target_link_libraries(cv_edge ${OpenCV_LIBS})
