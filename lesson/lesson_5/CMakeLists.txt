cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_BUILD_TYPE debug)
project(ncnn_lession5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src)
add_subdirectory(examples)
