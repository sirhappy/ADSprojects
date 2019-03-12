add_executable(broken_dna_test_start
    # linked list and brokendna tests
    # linked list and brokendna sources
    ${CMAKE_SOURCE_DIR}/../../src/linked_list.h
    ${CMAKE_SOURCE_DIR}/../../src/linked_list.hpp
    ${CMAKE_SOURCE_DIR}/../../src/dna_element.h
    ${CMAKE_SOURCE_DIR}/../../src/dna_element.cpp
    ${CMAKE_SOURCE_DIR}/../../src/dna_repairer.h
    ${CMAKE_SOURCE_DIR}/../../src/dna_repairer.cpp    
    # gtest sources
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest_main.cc
)
