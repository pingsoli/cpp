cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

# Output the statistic of execution time.
# set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
# set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# set(CMAKE_CXX_FLAGS "-fno-elide-constructors")
# set(CMAKE_CXX_FLAGS "-O3")  # optimize level
# set(CMAKE_CXX_FLAGS "-fdump-tree-optimized")  # optimization, gcc only

################################################################################
add_executable(future        future.cpp)
target_link_libraries(future pthread)

add_executable(big_and_little_endian                      big_and_little_endian.cpp)
add_executable(compute_elapsed_time                       compute_elapsed_time.cpp)
add_executable(const_trick                                const_trick.cpp)
add_executable(constexpr_and_const                        constexpr_and_const.cpp)
add_executable(deprecated                                 deprecated_keyword.cpp)
add_executable(extern_main                                extern_main.cpp extern_keyword.cpp)
add_executable(functor                                    functor.cpp)
add_executable(initializer_list                           initializer_list.cpp)
add_executable(mutable_keyword                            mutable_keyword.cpp)
add_executable(namespace                                  namespace.cpp)
add_executable(operator_new                               operator_new.cpp)
add_executable(ordered_and_unordered_map                  ordered_and_unordered_map.cpp)
add_executable(override_and_overload                      override_and_overload.cpp)
add_executable(pass_a_polymorphic_object_to_stl_algorithm pass_a_polymorphic_object_to_stl_algorithm.cpp)
add_executable(return_value_optimization                  return_value_optimization.cpp)
add_executable(template_function                          template_function.cpp)
add_executable(variadic_function                          variadic_function.cpp)
add_executable(vector_growth                              vector_growth.cpp)
add_executable(volatile                                   volatile.cpp)
add_executable(random_number                              random_number.cpp)
add_executable(data_alignment                             data_alignment.cpp)

# set(CMAKE_VERBOSE_MAKEFILE ON)
add_executable(vptr                                       vptr.cpp)
# Check the output file in 'CMakeFiles/CMakeFiles/vptr.dir' directory.
set_target_properties(vptr PROPERTIES COMPILE_FLAGS "-fdump-class-hierarchy")

add_executable(number_system_conversion                   number_system_conversion.cpp)
add_executable(two_star_pointer                           two_star_pointer.cpp)
add_executable(virtuality                                 virtuality.cpp)
add_executable(empty_base_optimization                    empty_base_optimization.cpp)
add_executable(decltype                                   decltype.cpp)
add_executable(stringstream                               stringstream.cpp)

add_executable(using_and_typedef using_and_typedef.cpp)
add_executable(pointer_and_reference pointer_and_reference.cpp)
add_executable(noncopyable noncopyable.cpp)
add_executable(inheritance inheritance.cpp)
add_executable(shallow_and_deep_copy shallow_and_deep_copy.cpp)

add_executable(timer timer.cpp)
target_link_libraries(timer -pthread)

add_executable(know_variable_type know_variable_type.cpp)
add_executable(auto auto.cpp)
add_executable(enum enum.cpp)
add_executable(override override.cpp)
add_executable(constructor constructor.cpp)
add_executable(lambda lambda.cpp)
add_executable(variadic_template variadic_template.cpp)

add_executable(pimplMain pimplMain.cpp pimpl.cpp)
add_executable(overload_universal_references overload_universal_references.cpp)
add_executable(SFINAE SFINAE.cpp)
add_executable(tag_dispatch tag_dispatch.cpp)
add_executable(bit_field bit_field.cpp)
add_executable(template_partial_specialization template_partial_specialization.cpp)
add_executable(overloading overloading.cpp)
add_executable(overriding overriding.cpp)
add_executable(hiding hiding.cpp)
add_executable(try_catch try_catch.cpp)
add_executable(diamond_problem_of_multiple_inheritance diamond_problem_of_multiple_inheritance.cpp)

add_executable(final_keyword final_keyword.cpp)

add_executable(encode_varint32 encode_varint32.cpp)
add_executable(short_string_optimization short_string_optimization.cpp)
