cmake_minimum_required(VERSION 3.10)

project(duration VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Release")

include_directories(./include)

add_executable(duration ./main.cpp)


