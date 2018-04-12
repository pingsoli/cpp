set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(listing_9.2 listing_9.2.cpp)
target_link_libraries(listing_9.2 pthread)
