cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(exception exception.cpp)
add_executable(exceptions_in_destructors exceptions_in_destructors.cpp)
add_executable(exception_and_terminate exception_and_terminate.cpp)
target_link_libraries(exception_and_terminate -pthread)
