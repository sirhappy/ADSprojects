cmake_minimum_required(VERSION 3.9)
project(skies)

set(CMAKE_CXX_STANDARD 11)

add_executable(skies
        main.cpp
        ReadWriter.h
        Solver.h
        Student_and_Ski.h)
