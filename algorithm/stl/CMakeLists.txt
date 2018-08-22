cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_RQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(stable_partition_position stable_partition_position.cpp)
add_executable(sort_subrange sort_subrange.cpp)
