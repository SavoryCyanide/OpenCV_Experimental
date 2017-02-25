cmake_minimum_required(VERSION 2.8)

project(hull)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_hull hull.cpp)

target_link_libraries(cv_hull ${OpenCV_LIBS})
