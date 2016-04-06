cmake_minimum_required(VERSION 2.8)
project(Codes) 
set(EXECUTABLE_OUTPUT_PATH,${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH,${PROJECT_BINARY_DIR}/lib) 
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(base)
add_subdirectory(net)

