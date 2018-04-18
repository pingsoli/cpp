cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "-fno-elide-constructors")

add_executable(ordered_and_unordered_map ordered_and_unordered_map.cpp)
add_executable(operator_new              operator_new.cpp)
add_executable(constexpr_and_const       constexpr_and_const.cpp)
add_executable(initializer_list          initializer_list.cpp)
add_executable(namespace                 namespace.cpp)
add_executable(template_function         template_function.cpp)
add_executable(vector_growth             vector_growth.cpp)
add_executable(unique_ptr                unique_ptr.cpp)
add_executable(mutable_keyword           mutable_keyword.cpp)
add_executable(override_and_overload     override_and_overload.cpp)
add_executable(deprecated                deprecated_keyword.cpp)
add_executable(big_and_little_endian     big_and_little_endian.cpp)
add_executable(const_trick               const_trick.cpp)
add_executable(return_value_optimization return_value_optimization.cpp)

add_executable(future        future.cpp)
target_link_libraries(future pthread)

add_executable(functor              functor.cpp)
add_executable(smart_ptr            smart_ptr.cpp)
add_executable(compute_elapsed_time compute_elapsed_time.cpp)

add_executable(thread_local        thread_local.cpp)
target_link_libraries(thread_local pthread)

add_executable(extern_main extern_main.cpp extern_keyword.cpp)
add_executable(pass_a_polymorphic_object_to_stl_algorithm pass_a_polymorphic_object_to_stl_algorithm.cpp)

add_executable(variadic_function variadic_function.cpp)
