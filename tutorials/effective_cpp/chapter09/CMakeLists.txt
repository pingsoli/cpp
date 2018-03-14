cmake_minimum_required( VERSION 3.4.1 )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic" )
set( CMAKE_BUILD_TYPE Debug )

add_executable(53 53.cpp)
add_executable(54 54.cpp)
