cmake_minimum_required(VERSION 3.0)

project(btree CXX)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)


# note https://stackoverflow.com/questions/6312151/stricmp-with-mingw-and-c0x-not-existent
# to enable c++11 (nullptr and so on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(INTERMEDIATE_DIR ${CMAKE_CURRENT_BINARY_DIR}/intermediate)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${INTERMEDIATE_DIR}/sol)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../tests ${INTERMEDIATE_DIR}/tests)
