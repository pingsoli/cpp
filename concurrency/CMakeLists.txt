cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMKAE_BUILD_TYPE Debug)

add_executable(atomic_access atomic_access.cpp)
target_link_libraries(atomic_access pthread)

add_executable(future future.cpp)
target_link_libraries(future pthread)

add_executable(atomic atomic.cpp)
target_link_libraries(atomic pthread)

add_executable(is_lock_free is_lock_free.cpp)
target_link_libraries(is_lock_free -latomic)
