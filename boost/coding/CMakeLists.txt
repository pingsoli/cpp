cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

## Boost Configure
set(Boost_USE_STATIC_LIBS    ON)  # force use static library.
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS    ON)  # read from hints only, not use system paths.

# Read hint from BOOST_ROOT variable
set(BOOST_ROOT "/usr/local/boost")

find_package(Boost 1.66.0)
if (Boost_FOUND)

  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})

  # print boost information
  message("\tboost include path:  ${Boost_INCLUDE_DIRS}")
  message("\tboost library path:  ${Boost_LIBRARY_DIRS}")
  message("\tboost version:       ${Boost_VERSION}")
  message("\tboost lib version:   ${Boost_LIB_VERSION}")

  add_executable(know_async_task know_async_task.cpp)
  target_link_libraries(know_async_task
    boost_system -pthread)

  add_executable(generic_server generic_server.cpp)
  target_link_libraries(generic_server
    boost_system -pthread)

endif()
