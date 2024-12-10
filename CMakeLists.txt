cmake_minimum_required(VERSION 3.14)
project(image_inverter_using_multithreading)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include path
include_directories("include")

# ImageInverter lib
add_library(image_inverter "src/ImageInverter.cpp")

# main
add_executable(main "src/main.cpp")

# linking main and ThreadPool lib
target_link_libraries(main PRIVATE image_inverter)
