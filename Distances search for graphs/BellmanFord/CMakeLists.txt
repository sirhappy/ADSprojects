cmake_minimum_required(VERSION 3.9)
project(BellmanFord)

set(CMAKE_CXX_STANDARD 11)

add_executable(BellmanFord main.cpp Edge.h ReadWriter.h)