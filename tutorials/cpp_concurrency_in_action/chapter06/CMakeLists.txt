cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(listing_6.1 listing_6.1.cpp)
target_link_libraries(listing_6.1 pthread)

add_executable(listing_6.2 listing_6.2.cpp)
target_link_libraries(listing_6.2 pthread)

add_executable(listing_6.3 listing_6.3.cpp)
target_link_libraries(listing_6.3 pthread)

add_executable(listing_6.4 listing_6.4.cpp)
target_link_libraries(listing_6.4 pthread)

add_executable(listing_6.5 listing_6.5.cpp)
target_link_libraries(listing_6.5 pthread)

add_executable(listing_6.6 listing_6.6.cpp)
target_link_libraries(listing_6.6 pthread)

add_executable(listing_6.10 listing_6.10.cpp)
target_link_libraries(listing_6.10 pthread)

set(Boost_USE_STATIC_LIBS    ON)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost 1.66.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(listing_6.11 listing_6.11.cpp)
target_link_libraries(listing_6.11 pthread boost_system)
