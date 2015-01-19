cmake_minimum_required(VERSION 2.8)
project(Utilities CXX) 


set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-std=c++11")


include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(test)
add_subdirectory(src)

enable_testing()
add_test(NAME get_first_follow_test COMMAND get_first_follow_test)
add_test(NAME log_unit_test COMMAND logTest)
