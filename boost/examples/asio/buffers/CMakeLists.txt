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

##############################
add_executable(server
  reference_counted.cpp
)

target_link_libraries(server
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

