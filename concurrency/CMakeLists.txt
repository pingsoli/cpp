cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(atomic_access atomic_access.cpp)
target_link_libraries(atomic_access -pthread)

add_executable(future future.cpp)
target_link_libraries(future -pthread)

add_executable(atomic atomic.cpp)
target_link_libraries(atomic -pthread)

add_executable(is_lock_free is_lock_free.cpp)
target_link_libraries(is_lock_free -latomic)

add_executable(promise promise.cpp)
#target_link_libraries(promise -pthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
target_link_libraries(promise Threads::Threads)

add_executable(promise_and_future promise_and_future.cpp)
target_link_libraries(promise_and_future -pthread)

add_executable(shared_future shared_future.cpp)
target_link_libraries(shared_future -pthread)

add_executable(ThreadPool ThreadPool.cpp)
target_link_libraries(ThreadPool -pthread)

add_executable(create_future create_future.cpp)
target_link_libraries(create_future -pthread)

add_executable(hardware_thread_num hardware_thread_num.cpp)
target_link_libraries(hardware_thread_num -pthread)

add_executable(ThreadRAII ThreadRAII.cpp)
target_link_libraries(ThreadRAII -pthread)

add_executable(async async.cpp)
target_link_libraries(async -pthread)
