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
add_executable(sender
  sender.cpp
)

target_link_libraries(sender
  boost_system
  pthread
)

add_executable(receiver
  receiver.cpp
)

target_link_libraries(receiver
  boost_system
  pthread
)
