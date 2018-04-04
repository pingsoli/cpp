set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(listing_7.1 listing_7.1.cpp)
target_link_libraries(listing_7.1 pthread)

add_executable(listing_7.2 listing_7.2.cpp)
target_link_libraries(listing_7.2 pthread)

add_executable(listing_7.3 listing_7.3.cpp)
target_link_libraries(listing_7.3 pthread)

add_executable(listing_7.10 listing_7.10.cpp)
target_link_libraries(listing_7.10 pthread)
