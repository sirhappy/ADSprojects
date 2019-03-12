cmake_minimum_required(VERSION 3.9)
project(Compression)

set(CMAKE_CXX_STANDARD 11)

add_executable(Compression
        main.cpp
        Node.h
        ReadWriter.h)
