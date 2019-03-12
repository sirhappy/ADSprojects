add_executable(safe_array_test_start 
    # array tests
    safearray_test.cpp
    subject_test.cpp
    # array sources
    ${CMAKE_SOURCE_DIR}/../../src/safearray.h
    ${CMAKE_SOURCE_DIR}/../../src/safearray.hpp
    ${CMAKE_SOURCE_DIR}/../../src/subject.h
    ${CMAKE_SOURCE_DIR}/../../src/subject.cpp
    # gtest sources
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest_main.cc
)
