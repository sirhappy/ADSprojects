add_executable(btree_test_start
    individual.h
    btree1_tests.cpp
    adapters1_tests.cpp
    ${CMAKE_SOURCE_DIR}/../../src/utils.h
    ${CMAKE_SOURCE_DIR}/../../src/btree.h
    ${CMAKE_SOURCE_DIR}/../../src/btree.cpp
    ${CMAKE_SOURCE_DIR}/../../src/btree_adapters.h
    # прямое включение сырцов gtest-а
    #${CMAKE_CURRENT_SOURCE_DIR}/gtest-fus/gtest.h          # в принципе, он менятся не должен
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest-fus/gtest-all.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest-fus/gtest_main.cc
)

# это тоже больше не нужно
#target_link_libraries(btree_test_start ${gtest_LIB} ${gtest_main_LIB})
