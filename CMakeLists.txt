project(multithreading_with_thread_pool)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include path
include_directories("include")

# ThreadPool lib
add_library(thread_pool "src/ThreadPool.cpp")

# main
add_executable(main "src/main.cpp")

# linking main and ThreadPool lib
target_link_libraries(main PRIVATE thread_pool)
