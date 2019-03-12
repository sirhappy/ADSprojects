cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bidi_linked_list.h
        bidi_linked_list.hpp
        main.cpp)

add_executable(src ${SOURCE_FILES})