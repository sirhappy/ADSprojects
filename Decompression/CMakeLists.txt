cmake_minimum_required(VERSION 3.9)
project(Decompression)

set(CMAKE_CXX_STANDARD 11)

add_executable(Decompression
        main.cpp
        Node.h
        ReadWriter.h)
