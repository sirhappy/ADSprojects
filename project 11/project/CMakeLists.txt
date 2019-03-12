cmake_minimum_required(VERSION 3.7)
project(project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main/main.cpp
        src/main/rbtree.h
        src/main/rbtree.hpp
        src/tests/def_dumper.h
        src/tests/individual.h
        src/tests/rbtree_prv1_test.cpp
        src/tests/rbtree_pub1_test.cpp)

add_executable(project ${SOURCE_FILES})