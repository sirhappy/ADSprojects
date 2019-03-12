cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        city.h
        main.cpp
        priority_queue.h
        rail_system.cpp
        rail_system.h
        service.h)

add_executable(src ${SOURCE_FILES})