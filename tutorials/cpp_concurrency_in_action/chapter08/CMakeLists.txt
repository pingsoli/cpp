cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(listing_8.3 listing_8.3.cpp)
target_link_libraries(listing_8.3 pthread)
