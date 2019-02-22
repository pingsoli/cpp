cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# Boost Configure
# set(Boost_NO_SYSTEM_PATH true)
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED ON)

set(BOOST_ROOT /usr/local/boost)

find_package(Boost REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# add_definitions( -DBOOST_ALL_NO_LIB )
# add_definitions( -DBOOST_ALL_DYN_LINK )

##############################
add_executable(http_client_sync
  http_client_sync.cpp
)

target_link_libraries(http_client_sync
  ${BOOST_ROOT}/lib/libboost_thread.so
  -pthread
)

add_executable(http_client_async
  http_client_async.cpp
)

target_link_libraries(http_client_async
  ${BOOST_ROOT}/lib/libboost_thread.so
  -pthread
)
