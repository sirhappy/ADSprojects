cmake_minimum_required(VERSION 3.9)
project(Check)

set(CMAKE_CXX_STANDARD 11)

add_executable(Check main.cpp A.hpp B.hpp B.cpp)