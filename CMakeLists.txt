cmake_minimum_required(VERSION 4.0)
project(LaneDetection)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 20)

add_executable(LaneDetection main.cpp
        src/process_video.cpp
        include/process_video.h)

target_include_directories(LaneDetection PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(LaneDetection ${OpenCV_LIBS})
