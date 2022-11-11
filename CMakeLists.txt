cmake_minimum_required(VERSION 3.23)

project(trie)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-fconstexpr-ops-limit=4294967296")

enable_testing()

set(TEST_EXECUTABLE tests)
set(BENCHMARK_EXECUTABLE benchmarks)

file(GLOB_RECURSE TESTS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/test/*)
file(GLOB_RECURSE BENCHMARKS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/benchmark/*)

add_executable(${TEST_EXECUTABLE} ${TESTS})
add_executable(${BENCHMARK_EXECUTABLE} ${BENCHMARKS})
add_executable(demo src/demo.cpp)
add_executable(static_demo src/static_demo.cpp)

target_include_directories(${TEST_EXECUTABLE} PUBLIC GTEST_INCLUDE_DIRS PUBLIC ${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(${TEST_EXECUTABLE} GTest::gtest_main)
target_include_directories(${BENCHMARK_EXECUTABLE} PUBLIC ${PROJECT_SOURCE_DIR}/src/)
target_link_libraries(${BENCHMARK_EXECUTABLE} benchmark::benchmark_main)

add_test(tests ${TEST_EXECUTABLE})
