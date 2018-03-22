set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(listing_4.1 listing_4.1.cpp)
target_link_libraries(listing_4.1 pthread)

add_executable(listing_4.5 listing_4.5.cpp)
target_link_libraries(listing_4.5 pthread)

add_executable(listing_4.6 listing_4.6.cpp)
target_link_libraries(listing_4.6 pthread)

add_executable(listing_4.7 listing_4.7.cpp)
target_link_libraries(listing_4.7 pthread)

add_executable(listing_4.12 listing_4.12.cpp)
target_link_libraries(listing_4.12 pthread)

add_executable(listing_4.13 listing_4.13.cpp)
target_link_libraries(listing_4.13 pthread)
