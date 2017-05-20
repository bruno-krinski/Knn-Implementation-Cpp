cmake_minimum_required (VERSION 3.5.0)

project (K-Nearest-Neighbour)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
#set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
 
#include_directories("${PROJECT_INCLUDE_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}")
 
add_subdirectory(Classify/build)
add_subdirectory(GenFeatures/build)
