cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_RQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(quick_sort     quick_sort.cpp)
add_executable(shell_sort     shell_sort.cpp)
add_executable(merge_sort     merge_sort.cpp)
add_executable(heap_sort      heap_sort.cpp)
add_executable(insertion_sort insertion_sort.cpp)
add_executable(selection_sort selection_sort.cpp)
