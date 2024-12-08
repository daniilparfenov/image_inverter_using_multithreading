project(image_inverter_using_multithreading)
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include path
include_directories("include")

# BlockingQueue lib
add_library(blocking_queue "src/BlockingQueue.cpp")

# ImageInverter lib
add_library(image_inverter "src/ImageInverter.cpp")
target_link_libraries(image_inverter PRIVATE blocking_queue)

# main
add_executable(main "src/main.cpp")

# linking main and ThreadPool lib
target_link_libraries(main PRIVATE image_inverter blocking_queue)
