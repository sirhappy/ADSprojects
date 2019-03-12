add_executable(bidi_list_test_start 
    # bidi list tests
    bidi_linked_list_test.cpp
    # bidi list sources
    ${CMAKE_SOURCE_DIR}/../../src/bidi_linked_list.h
    ${CMAKE_SOURCE_DIR}/../../src/bidi_linked_list.hpp
    # gtest sources
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest_main.cc
)
