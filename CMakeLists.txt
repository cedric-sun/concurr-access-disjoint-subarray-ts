cmake_minimum_required(VERSION 3.17)
project(concurr_access_disjoint_subarray_ts C)

set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(main main.c)
target_link_libraries(main PRIVATE Threads::Threads)

add_executable(alternative alternative.c)
target_link_libraries(alternative PRIVATE Threads::Threads)

add_executable(byte-test byte-test.c)
target_link_libraries(byte-test PRIVATE Threads::Threads)
