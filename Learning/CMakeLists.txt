cmake_minimum_required(VERSION 3.7)
project(Learning)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Window_mgr.h Screen.h)
add_executable(Learning ${SOURCE_FILES})