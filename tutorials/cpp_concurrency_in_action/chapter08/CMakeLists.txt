cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(listing_8.3 listing_8.3.cpp)
target_link_libraries(listing_8.3 pthread)

add_executable(listing_8.4 listing_8.4.cpp)
target_link_libraries(listing_8.4 pthread)

add_executable(listing_8.5 listing_8.5.cpp)
target_link_libraries(listing_8.5 pthread)

add_executable(listing_8.10 listing_8.10.cpp)
target_link_libraries(listing_8.10 pthread)

add_executable(listing_8.11 listing_8.11.cpp)
target_link_libraries(listing_8.11 pthread)

add_executable(listing_8.13 listing_8.13.cpp)
target_link_libraries(listing_8.13 pthread)
