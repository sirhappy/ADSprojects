cmake_minimum_required(VERSION 3.9)
project(calculator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE  Token.h
            Token.cpp
            main.cpp)
add_executable(calculator ${SOURCE})