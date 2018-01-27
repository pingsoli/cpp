cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

##############################
add_executable(observer
  observer.cpp)

##############################
add_executable(singleton
  singleton.cpp)
