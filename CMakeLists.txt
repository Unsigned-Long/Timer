cmake_minimum_required(VERSION 3.10)

project(duration VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_INSTALL_PREFIX /usr/local)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/include/ DESTINATION include/artwork/timer)
