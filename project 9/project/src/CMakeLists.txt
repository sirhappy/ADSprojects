cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        dictionary.h
        hashset.cpp
        hashset.h
        main.cpp)

add_executable(src ${SOURCE_FILES})