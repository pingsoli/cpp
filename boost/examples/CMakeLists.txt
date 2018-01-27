cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(INCLUDE_DIR ..)
set(LIBRARY_DIR ..)
set(BINARY_DIR ..)

# Boost Configure
set(Boost_USE_STATIC_LIBS    ON)
#set(Boost_USE_MULTITHREADED  ON)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost 1.66.0)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

#set(EXECUTABLE_OUTPUT_PATH ${BINARY_DIR}/bin)

##############################
add_executable(main
  main.cpp)

target_link_libraries(main
  ${BOOST_ROOT}/lib/libboost_regex.a)

##############################
add_executable(coroutine
  coroutine.cpp)

target_link_libraries(coroutine
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)

##############################
add_executable(smart_pointer
  smart_pointer.cpp
)

##############################
add_executable(shared_ptr
  shared_ptr.cpp
)

##############################
