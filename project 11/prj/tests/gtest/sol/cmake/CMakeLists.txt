include(${CMAKE_CURRENT_SOURCE_DIR}/UserParams.cmake)

include_directories(${CMAKE_SOURCE_DIR}/../../src) #for the main project
include_directories(${gtest_INCLUDE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${CMAKE_CURRENT_BINARY_DIR}/src)
