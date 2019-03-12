cmake_minimum_required(VERSION 3.9)
project(mergesort)

set(CMAKE_CXX_STANDARD 11)

add_executable(mergesort
        main.cpp
        MergeSort.h
        ReadWriter.h)
