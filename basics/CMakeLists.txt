cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

##############################
add_executable(operator_overload
  operator_overload.cpp
)

##############################
add_executable(ordered_and_unordered_map
  ordered_and_unordered_map.cpp
)

##############################
add_executable(operator_new
  operator_new.cpp
)
