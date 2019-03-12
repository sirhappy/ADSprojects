include_directories(${CMAKE_SOURCE_DIR}/../../src) #for the main project

# add test gtest includings (must be done BEFORE adding main test source folder)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src/gtest)

# add test sources (main test project)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../src ${CMAKE_CURRENT_BINARY_DIR}/src)
