cmake_minimum_required( VERSION 3.4.1 )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
set( CMAKE_BUILD_TYPE Debug )

add_executable(26 26.cpp)
add_executable(27 27.cpp)
add_executable(28 28.cpp)
add_executable(29 29.cpp)
add_executable(30 30.cpp)
add_executable(31
  31.cpp
  Person.cpp
  PersonImpl.cpp
  Date.cpp)
