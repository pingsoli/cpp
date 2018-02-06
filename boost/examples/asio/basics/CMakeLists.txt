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
add_executable(sync_timer
  sync_timer.cpp
)

target_link_libraries(sync_timer
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(async_timer
  async_timer.cpp
)

target_link_libraries(async_timer
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(bind_args
  bind_args.cpp
)

target_link_libraries(bind_args
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(bind_member_function
  bind_member_function.cpp
)

target_link_libraries(bind_member_function
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

##############################
add_executable(strand
  strand.cpp
)

target_link_libraries(strand
  ${BOOST_ROOT}/lib/libboost_date_time.a
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_thread.a
  pthread
)

