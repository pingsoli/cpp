set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

################################################################################
add_executable(accumulate accumulate.cpp)
#add_executable(reduce reduce.cpp)
add_executable(set set.cpp)
add_executable(vector vector.cpp)
add_executable(string string.cpp)
add_executable(multimap multimap.cpp)
add_executable(map map.cpp)
add_executable(iterator iterator.cpp)
