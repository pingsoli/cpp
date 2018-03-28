cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-fno-elide-constructors")

add_executable(ordered_and_unordered_map ordered_and_unordered_map.cpp)
add_executable(operator_new              operator_new.cpp)
add_executable(constexpr_and_const       constexpr_and_const.cpp)
add_executable(initializer_list          initializer_list.cpp)
add_executable(namespace                 namespace.cpp)
add_executable(cpp_test                  test.cpp)
add_executable(template_function         template_function.cpp)
add_executable(vector_test               vector_test.cpp)
add_executable(unique_ptr                unique_ptr.cpp)
