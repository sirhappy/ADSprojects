cmake_minimum_required(VERSION 3.7)
project(S5NiceQueueTmpl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        S5NiceQueueTmpl/src/main.cpp
        S5NiceQueueTmpl/src/NiceQueue.h
        S5NiceQueueTmpl/src/NiceStack.h
        S5NiceQueueTmpl/src/NiceQueue.hpp
        S5NiceQueueTmpl/src/NiceStack.hpp)

add_executable(S5NiceQueueTmpl ${SOURCE_FILES})