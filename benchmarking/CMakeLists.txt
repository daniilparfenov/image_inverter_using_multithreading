# benchmarking tests
file(GLOB BENCHMARK_TEST_FILES "BenchmarkSingleThread.cpp")
add_executable(benchmark_single_thread ${BENCHMARK_TEST_FILES})
target_link_libraries(benchmark_single_thread PRIVATE single_thread ${OpenCV_LIBS})

# benchmarking tests
file(GLOB BENCHMARK_TEST_FILES "BenchmarkMultiThread.cpp")
add_executable(benchmark_multi_thread ${BENCHMARK_TEST_FILES})
target_link_libraries(benchmark_multi_thread PRIVATE image_inverter ${OpenCV_LIBS})
