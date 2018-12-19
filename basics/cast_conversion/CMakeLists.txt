cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(const_cast const_cast.cpp)
add_executable(static_cast static_cast.cpp)
add_executable(dynamic_cast dynamic_cast.cpp)
add_executable(reinterpret_cast reinterpret_cast.cpp)
