cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(cohabitate cohabitate_std_and_boost_shared_ptr.cpp)
add_executable(unique_ptr unique_ptr.cpp)
add_executable(smart_ptr smart_ptr.cpp)
add_executable(enable_shared_from_this enable_shared_from_this.cpp)
add_executable(weak_ptr weak_ptr.cpp)
add_executable(make_shared make_shared.cpp)
