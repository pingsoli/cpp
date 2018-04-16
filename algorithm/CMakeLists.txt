cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_RQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(string string.cpp)
add_executable(binary_search binary_search.cpp)
add_executable(beautiful_std_alg beautiful_std_alg.cpp)
add_executable(quick_sort quick_sort.cpp)
add_executable(bfs BFS.cpp)
add_executable(dfs DFS.cpp)
add_executable(reverse_integer reverse_integer.cpp)
add_executable(kmp KMP.cpp)
add_executable(binary_search_tree binary_search_tree.cpp)
add_executable(dijkstra Dijkstra.cpp)
add_executable(8_queens_puzzle 8_queens_puzzle.cpp)
