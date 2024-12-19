cmake_minimum_required(VERSION 3.14)
project(image_inverter_using_multithreading)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV include
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# include path
include_directories("include")

# ImageInverter lib
add_library(image_inverter "src/ImageInverter.cpp")
target_link_libraries(image_inverter ${OpenCV_LIBS})

# Single Thread lib
add_library(single_thread "src/SingleThreadInverter.cpp")
target_link_libraries(single_thread ${OpenCV_LIBS})

# main
add_executable(main "src/main.cpp")

# linking main and ThreadPool lib
target_link_libraries(main PRIVATE image_inverter ${OpenCV_LIBS})

# flag to enable/disable benchmark compilation
option(BUILD_BENCHMARK "Build benchmark files" ON)
if (BUILD_BENCHMARK) 
  add_subdirectory(benchmarking)
endif()
