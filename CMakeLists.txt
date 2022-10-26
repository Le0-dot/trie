cmake_minimum_required(VERSION 3.23)

project(prefix_tree)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#enable_testing()

set(TEST_EXECUTABLE tests)

file(GLOB_RECURSE TESTS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/test/*)

#add_executable(${TEST_EXECUTABLE} ${TESTS})
add_executable(demo src/demo.cpp)

#target_include_directories(${TEST_EXECUTABLE} PUBLIC GTEST_INCLUDE_DIRS PUBLIC src/)
#target_link_libraries(${TEST_EXECUTABLE} GTest::gtest_main)

#add_test(tests ${TEST_EXECUTABLE})
