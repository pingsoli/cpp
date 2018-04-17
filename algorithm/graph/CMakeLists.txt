cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_RQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(bfs                                   BFS.cpp)
add_executable(dfs                                   DFS.cpp)
add_executable(dijkstra                              Dijkstra.cpp)
add_executable(letter_combinations_of_a_phone_number letter_combinations_of_a_phone_number.cpp)
