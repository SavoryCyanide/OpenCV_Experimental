cmake_minimum_required(VERSION 2.8)

project(blur)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_blur blur.cpp)

target_link_libraries(cv_blur ${OpenCV_LIBS})
