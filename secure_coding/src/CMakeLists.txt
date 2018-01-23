cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)  # -std=c++11

# Boost_1_66_0
# Locate platform specific BOOST
set(Boost_USE_STATIC           ON)  # only find static libs
set(Boost_USE_MULTITHREAD      ON)
set(Boost_USE_STATIC_RUNTIME   OFF)
set(BOOST_ROOT /usr/local/boost)

find_package(Boost 1.66)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()


# Search all *.cpp file
file(GLOB_RECURSE SOURCES "./*.cpp")

# Set binary output path
set(EXECUTABLE_OUTPUT_PATH "../bin")

add_executable(main
  ${SOURCES}
)
