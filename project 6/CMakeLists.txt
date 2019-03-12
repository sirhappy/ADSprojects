cmake_minimum_required(VERSION 3.7)
project(project_6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        prj/src/bidi_linked_list.h
        prj/src/bidi_linked_list.hpp
        prj/src/main.cpp
        prj/tests/gtest/src/gtest/internal/custom/gtest-port.h
        prj/tests/gtest/src/gtest/internal/custom/gtest-printers.h
        prj/tests/gtest/src/gtest/internal/custom/gtest.h
        prj/tests/gtest/src/gtest/internal/gtest-death-test-internal.h
        prj/tests/gtest/src/gtest/internal/gtest-filepath.h
        prj/tests/gtest/src/gtest/internal/gtest-internal.h
        prj/tests/gtest/src/gtest/internal/gtest-linked_ptr.h
        prj/tests/gtest/src/gtest/internal/gtest-param-util-generated.h
        prj/tests/gtest/src/gtest/internal/gtest-param-util.h
        prj/tests/gtest/src/gtest/internal/gtest-port-arch.h
        prj/tests/gtest/src/gtest/internal/gtest-port.h
        prj/tests/gtest/src/gtest/internal/gtest-string.h
        prj/tests/gtest/src/gtest/internal/gtest-tuple.h
        prj/tests/gtest/src/gtest/internal/gtest-type-util.h
        prj/tests/gtest/src/gtest/src/gtest-death-test.cc
        prj/tests/gtest/src/gtest/src/gtest-filepath.cc
        prj/tests/gtest/src/gtest/src/gtest-internal-inl.h
        prj/tests/gtest/src/gtest/src/gtest-port.cc
        prj/tests/gtest/src/gtest/src/gtest-printers.cc
        prj/tests/gtest/src/gtest/src/gtest-test-part.cc
        prj/tests/gtest/src/gtest/src/gtest-typed-test.cc
        prj/tests/gtest/src/gtest/src/gtest.cc
        prj/tests/gtest/src/gtest/gtest-all.cc
        prj/tests/gtest/src/gtest/gtest-death-test.h
        prj/tests/gtest/src/gtest/gtest-message.h
        prj/tests/gtest/src/gtest/gtest-param-test.h
        prj/tests/gtest/src/gtest/gtest-printers.h
        prj/tests/gtest/src/gtest/gtest-spi.h
        prj/tests/gtest/src/gtest/gtest-test-part.h
        prj/tests/gtest/src/gtest/gtest-typed-test.h
        prj/tests/gtest/src/gtest/gtest.h
        prj/tests/gtest/src/gtest/gtest_main.cc
        prj/tests/gtest/src/gtest/gtest_pred_impl.h
        prj/tests/gtest/src/gtest/gtest_prod.h
        prj/tests/gtest/src/bidi_linked_list_test.cpp)

add_executable(project_6 ${SOURCE_FILES})