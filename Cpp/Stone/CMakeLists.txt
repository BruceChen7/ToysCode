cmake_minimum_required(VERSION 2.8)
project(Compiler CXX)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_CXX_COMPILER "clang++-3.5")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "O2 -Wshadow")

include_directories(${PROJECT_SOURCE_DIR}/src/*.h)
add_subdirectory(src)
add_subdirectory(src/test)
 
enable_testing()
add_test(NAME test_lexical COMMAND test_lexical)

