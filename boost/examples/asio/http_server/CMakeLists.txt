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
add_executable(http_server
  connection.cpp
  connection_manager.cpp
  main.cpp
  mime_types.cpp
  reply.cpp
  request_handler.cpp
  request_parser.cpp
  server.cpp
)

target_link_libraries(http_server
  boost_system
  pthread
)
