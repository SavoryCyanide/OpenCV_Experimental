cmake_minimum_required(VERSION 2.8)

project(subtraction)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_subtraction subtraction.cpp)

target_link_libraries(cv_subtraction ${OpenCV_LIBS})
