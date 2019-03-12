cmake_minimum_required(VERSION 3.7)
project(KR)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/BinaryHeap.h src/BinaryHeap.hpp)
add_executable(KR ${SOURCE_FILES})