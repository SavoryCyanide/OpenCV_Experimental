cmake_minimum_required(VERSION 2.8)

project(video)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(cv_video video.cpp)

target_link_libraries(cv_video ${OpenCV_LIBS})
