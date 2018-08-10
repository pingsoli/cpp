cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Boost Configure
set(Boost_USE_STATIC_LIBS    ON)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost 1.66.0)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(know_async_task know_async_task.cpp)
target_link_libraries(know_async_task
  boost_system -pthread)

add_executable(generic_server generic_server.cpp)
target_link_libraries(generic_server
  boost_system -pthread)
