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
add_executable(chat_client
  chat_client.cpp
)

target_link_libraries(chat_client
  boost_date_time boost_system boost_thread
  pthread
)

##############################
add_executable(chat_server
  chat_server.cpp
)

target_link_libraries(chat_server
  boost_date_time boost_system boost_thread
  pthread
)
