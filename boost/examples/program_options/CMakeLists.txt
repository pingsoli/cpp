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
add_executable(first
  first.cpp
)

target_link_libraries(first
  ${BOOST_ROOT}/lib/libboost_program_options.a
)

##############################
add_executable(custom_syntax
  custom_syntax.cpp
)

target_link_libraries(custom_syntax
  ${BOOST_ROOT}/lib/libboost_program_options.a
)

##############################
add_executable(multiple_sources
  multiple_sources.cpp
)

target_link_libraries(multiple_sources
  ${BOOST_ROOT}/lib/libboost_program_options.a
)

##############################
add_executable(option_groups
  option_groups.cpp
)

target_link_libraries(option_groups
  ${BOOST_ROOT}/lib/libboost_program_options.a
)

##############################
add_executable(options_description
  options_description.cpp
)

target_link_libraries(options_description
  ${BOOST_ROOT}/lib/libboost_program_options.a
)

##############################
add_executable(real
  real.cpp
)

target_link_libraries(real
  ${BOOST_ROOT}/lib/libboost_program_options.a
)
