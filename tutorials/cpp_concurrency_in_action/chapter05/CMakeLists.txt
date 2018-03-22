set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(listing_1.1 listing_1.1.cpp)
target_link_libraries(listing_1.1 pthread)
