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
add_executable(fibonacci
  fibonacii.cpp
)

target_link_libraries(fibonacci
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)

##############################
add_executable(layout
  layout.cpp
)

target_link_libraries(layout
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)

##############################
add_executable(parser
  parser.cpp
)

target_link_libraries(parser
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)

##############################
add_executable(same_fringe
  same_fringe.cpp
)

target_link_libraries(same_fringe
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)

##############################
add_executable(segmented
  segmented.cpp
)

target_link_libraries(segmented
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)

##############################
add_executable(coroutine
  coroutine.cpp
)

target_link_libraries(coroutine
  ${BOOST_ROOT}/lib/libboost_coroutine.a
  ${BOOST_ROOT}/lib/libboost_context.a
  ${BOOST_ROOT}/lib/libboost_thread.a
)
