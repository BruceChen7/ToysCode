cmake_minimum_required(VERSION 2.8)
project(Cpp CXX) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "O2 -Wshadow")

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(Utilities)
add_subdirectory(Stone)

enable_testing()
