cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(local_static_variable           local_static_variable.cpp)
add_executable(global_static_variable          global_static_variable.cpp bar.cpp)
add_executable(static_variable_of_class_member static_variable_of_class_member.cpp)
