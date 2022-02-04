cmake_minimum_required(VERSION 3.10)

project(duration VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

include_directories(./include)

add_executable(duration ./main.cpp)

set(CMAKE_INSTALL_PREFIX /usr/local)

install(FILES ${CMAKE_SOURCE_DIR}/include/timer.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/artwork/timer)
