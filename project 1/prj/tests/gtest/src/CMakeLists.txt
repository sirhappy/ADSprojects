add_executable(xipoint_test_start 
    # point tests
    point_test.cpp
    point_array_test.cpp
    # point sources    
    ${CMAKE_SOURCE_DIR}/../../src/xipoint.cpp
    ${CMAKE_SOURCE_DIR}/../../src/xipoint.h
    # gtest sources
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest_main.cc
)
