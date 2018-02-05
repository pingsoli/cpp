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
add_executable(file_size
  file_size.cpp
)

target_link_libraries(file_size
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_filesystem.a
)

##############################
add_executable(exists
  exists.cpp
)

target_link_libraries(exists
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_filesystem.a
)

##############################
add_executable(directory_iterator
  directory_iterator.cpp
)

target_link_libraries(directory_iterator
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_filesystem.a
)

##############################
add_executable(path_decomposition
  path_decomposition.cpp
)

target_link_libraries(path_decomposition
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_filesystem.a
)

##############################
add_executable(recursive_path
  recursive_path.cpp
)

target_link_libraries(recursive_path
  ${BOOST_ROOT}/lib/libboost_system.a
  ${BOOST_ROOT}/lib/libboost_filesystem.a
)
