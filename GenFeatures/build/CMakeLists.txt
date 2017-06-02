cmake_minimum_required (VERSION 3.5.0)

project (K-Nearest-Neighbour-GenFeatures)

include_directories(../include)

set(SOURCES ../src/main.cpp ../src/Data.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set (GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -fopenmp -Ofast -Wall")
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set (EXECUTABLE_OUTPUT_PATH "../")

add_executable (genFeatures ${SOURCES})

target_link_libraries (genFeatures ${OpenCV_LIBS})
