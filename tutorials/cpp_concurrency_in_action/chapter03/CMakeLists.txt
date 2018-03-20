cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(listing_3.1 listing_3.1.cpp)
target_link_libraries(listing_3.1 pthread)

add_executable(listing_3.2 listing_3.2.cpp)
target_link_libraries(listing_3.2 pthread)

add_executable(listing_3.5 listing_3.5.cpp)
target_link_libraries(listing_3.5 pthread)

add_executable(listing_3.8 listing_3.8.cpp)
target_link_libraries(listing_3.8 pthread)

add_executable(listing_3.10 listing_3.10.cpp)
target_link_libraries(listing_3.10 pthread)

add_executable(listing_3.11 listing_3.11.cpp)
target_link_libraries(listing_3.11 pthread)

add_executable(listing_3.12 listing_3.12.cpp)
target_link_libraries(listing_3.12 pthread)

# include boost library
set(Boost_USE_STATIC_LIBS    ON)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost 1.66.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(listing_3.13 listing_3.13.cpp)
target_link_libraries(listing_3.13
  boost_thread boost_system)
