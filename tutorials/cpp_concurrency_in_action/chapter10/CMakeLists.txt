cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_PTHREAD_PREFER ON)
#find_package(Threads)

add_executable(listing_10.1 listing_10.1.cpp)
#target_link_libraries(listing_10.1 Threads::Threads)
target_link_libraries(listing_10.1 -pthread)
