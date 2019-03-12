add_executable(stack_machine_test_start 
    # stack machine tests
    int_stack_test.cpp
    stack_machine_test.cpp
    # stack machine sources
    ${CMAKE_SOURCE_DIR}/../../src/int_stack.cpp
    ${CMAKE_SOURCE_DIR}/../../src/int_stack.h
    ${CMAKE_SOURCE_DIR}/../../src/stack_machine.cpp
    ${CMAKE_SOURCE_DIR}/../../src/stack_machine.h
    # gtest sources
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/gtest_main.cc
)
