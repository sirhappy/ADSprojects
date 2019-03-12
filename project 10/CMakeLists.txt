cmake_minimum_required(VERSION 3.7)
project(project_10)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    src/main.cpp
    src/parts.h
    src/parts.cpp)

add_executable(project_10 ${SOURCE_FILES})