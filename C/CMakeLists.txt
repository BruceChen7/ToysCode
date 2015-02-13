cmake_minimum_required(VERSION 2.8)
project(TOYS_C C)


add_subdirectory(src) 
add_subdirectory(test)

enable_testing()
add_test(NAME sds_test COMMAND sds_test)

