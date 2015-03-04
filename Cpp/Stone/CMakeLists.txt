cmake_minimum_required(VERSION 2.8)
project(Compiler CXX)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_COMPILER "clang++")

include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME lexical_unit_test COMMAND lexical_unit_test)

