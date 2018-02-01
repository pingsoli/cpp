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
add_executable(join
  join.cpp
)

target_link_libraries(join
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
)

##############################
add_executable(range_for
  range_for.cpp
)

target_link_libraries(range_for
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
)

##############################
add_executable(simple
  simple.cpp
)

target_link_libraries(simple
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
)

##############################
add_executable(work_stealing
  work_stealing.cpp
)

target_link_libraries(work_stealing
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
  pthread
)

##############################
add_executable(ping_pong
  ping_pong.cpp
)

target_link_libraries(ping_pong
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
)

#############################
add_executable(buffered_chan
  buffered_channel.cpp
)

target_link_libraries(buffered_chan
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
)

##############################
add_executable(future
  future.cpp
)

target_link_libraries(future
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  ${BOOST_ROOT}/lib/libboost_fiber.a
)

##############################
add_executable(adapt_callbacks
  adapt_callbacks.cpp
)

target_link_libraries(adapt_callbacks
  ${BOOST_ROOT}/lib/libboost_fiber.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)
