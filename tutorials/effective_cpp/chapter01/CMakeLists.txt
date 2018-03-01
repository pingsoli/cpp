cmake_minimum_required( VERSION 3.4.1 )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
set( CMAKE_BUILD_TYPE Debug )

add_executable(1 01.cpp)
add_executable(2 02.cpp game_player.cpp)
add_executable(3 03.cpp)
add_executable(4 04.cpp)
