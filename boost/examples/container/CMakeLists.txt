cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Boost Configure
set(Boost_USE_STATIC_LIBS    ON)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(any any.cpp)
add_executable(circular_buffer circular_buffer.cpp)
