cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# Boost Configure
set(Boost_USE_STATIC_LIBS    ON)
set(BOOST_ROOT /usr/local/boost)
set(BOOST_INCS ${BOOST_ROOT}/include)
set(BOOST_LIBS ${BOOST_ROOT}/lib)

find_package(Boost 1.66.0)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

##############################
add_executable(main main.cpp)

target_link_libraries(main
  ${BOOST_LIBS}/libboost_system.a
  ${BOOST_LIBS}/libboost_log_setup.a
  ${BOOST_LIBS}/libboost_log.a
  ${BOOST_LIBS}/libboost_thread.a
  -pthread
)
