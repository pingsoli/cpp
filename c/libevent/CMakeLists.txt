cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set(LIBEVENT_ROOT /usr/local/libevent)
include_directories(${LIBEVENT_ROOT}/include)
link_directories(${LIBEVENT_ROOT}/lib)

add_executable(http_server http_server.c)
target_link_libraries(http_server
  libevent.a
  libevent_core.a
  libevent_pthreads.a
  libevent_extra.a
)

add_executable(http_client http_client.c)
target_link_libraries(http_client
  libevent.a
  libevent_core.a
  libevent_pthreads.a
  libevent_extra.a
)

add_executable(timer timer.c)
target_link_libraries(timer
  libevent.a
)
