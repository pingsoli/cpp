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
add_executable(tcp_client
  daytime_tcp_client.cpp
)

target_link_libraries(tcp_client
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(tcp_server
  daytime_tcp_server.cpp
)

target_link_libraries(tcp_server
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(async_server
  daytime_tcp_async_server.cpp
)

target_link_libraries(async_server
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(udp_client
  daytime_udp_client.cpp
)

target_link_libraries(udp_client
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(udp_server
  daytime_udp_server.cpp
)

target_link_libraries(udp_server
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(udp_async_server
  daytime_udp_async_server.cpp
)

target_link_libraries(udp_async_server
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(server
  daytime_combined_server.cpp
)

target_link_libraries(server
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

