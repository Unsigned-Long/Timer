cmake_minimum_required(VERSION 3.10)

project(learnCPP VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)

aux_source_directory(./src SRC_DIR)

add_executable(learnCPP ./main.cpp ${SRC_DIR})

