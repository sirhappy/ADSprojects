# т.к. убрали зависимость к gtest, это уже не актуально, но для общности оставляем
include(${CMAKE_CURRENT_SOURCE_DIR}/UserParams.cmake)

include_directories(${CMAKE_SOURCE_DIR}/../../src) #for the main project
#include_directories(${gtest_INCLUDE_DIR})      # убрали реф
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src) # чтобы иметь возможность найти gtest-fus/gtest.h
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${CMAKE_CURRENT_BINARY_DIR}/src)
