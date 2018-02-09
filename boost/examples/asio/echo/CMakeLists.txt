cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# Boost Configure
set(Boost_USE_STATIC_LIBS    ON)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost 1.66.0)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

##############################
add_executable(blocking_echo_tcp_client
  blocking_echo_tcp_client.cpp
)

target_link_libraries(blocking_echo_tcp_client
  boost_date_time boost_system boost_thread
  pthread
)

##############################
add_executable(blocking_echo_tcp_server
  blocking_echo_tcp_server.cpp
)

target_link_libraries(blocking_echo_tcp_server
  boost_date_time boost_system boost_thread
  pthread
)

##############################
add_executable(blocking_echo_udp_server
  blocking_echo_udp_server.cpp
)

target_link_libraries(blocking_echo_udp_server
  boost_date_time boost_system boost_thread
  pthread
)

##############################
add_executable(blocking_echo_udp_client
  blocking_echo_udp_client.cpp
)

target_link_libraries(blocking_echo_udp_client
  boost_date_time boost_system boost_thread
  pthread
)

##############################
add_executable(async_tcp_echo_server
  async_tcp_echo_server.cpp
)

target_link_libraries(async_tcp_echo_server
  boost_date_time boost_system boost_thread
  pthread
)

##############################
add_executable(async_udp_echo_server
  async_udp_echo_server.cpp
)

target_link_libraries(async_udp_echo_server
  boost_date_time boost_system boost_thread
  pthread
)

