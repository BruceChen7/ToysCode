cmake_minimum_required(VERSION 2.8)
project(Lispy)
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(utils)
add_subdirectory(tests)

set(src mpc.c calculate.c)
add_library(mpc ${src})

add_executable(calculate calculate.c mpc.c)
target_link_libraries(calculate mpc m)