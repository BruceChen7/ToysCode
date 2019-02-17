cmake_minimum_required(VERSION 3.7)
project(toys_c VERSION 1.21.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
# 用来生成compile_commands.json打开
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "-g -Werror -Wno-unused-but-set-variable -O2")
message(STATUS "CMAKE_C_FLAGS = " ${CMAKE_C_FLAGS})
include_directories(
    "${PROJECT_SOURCE_DIR}"
)

enable_testing()
# 定义test目标
function(toys_c_test test_file)
    get_filename_component(test_target_name "${test_file}" NAME_WE)
    add_executable("${test_target_name}" "")
    target_sources("${test_target_name}"
        PRIVATE
        "${test_file}")
    target_link_libraries("${test_target_name}"
        toys_c_lib)
    add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
endfunction(toys_c_test)

toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_sort.c")
toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_toys_list.c")
toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_toys_sds.c")
toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_time.c")
toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_mem.c")
toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_util.c")
toys_c_test("${PROJECT_SOURCE_DIR}/base/tests/test_vec.c")

add_library(toys_c_lib "")

#======================================================================
# 定义C目录下的源文件
#======================================================================
target_sources(toys_c_lib
  PRIVATE
    "${PROJECT_SOURCE_DIR}/base/binary_tree.c"
    "${PROJECT_SOURCE_DIR}/base/binary_tree.h"
    "${PROJECT_SOURCE_DIR}/base/graph.c"
    "${PROJECT_SOURCE_DIR}/base/graph.h"
    "${PROJECT_SOURCE_DIR}/base/queue.h"
    "${PROJECT_SOURCE_DIR}/base/sort.c"
    "${PROJECT_SOURCE_DIR}/base/sort.h"
    "${PROJECT_SOURCE_DIR}/base/string_.c"
    "${PROJECT_SOURCE_DIR}/base/string_.h"
    "${PROJECT_SOURCE_DIR}/base/toys_list.c"
    "${PROJECT_SOURCE_DIR}/base/toys_list.h"
    "${PROJECT_SOURCE_DIR}/base/toys_mem.c"
    "${PROJECT_SOURCE_DIR}/base/toys_mem.h"
    "${PROJECT_SOURCE_DIR}/base/toys_sds.c"
    "${PROJECT_SOURCE_DIR}/base/toys_sds.h"
    "${PROJECT_SOURCE_DIR}/base/toys_sds.h"
    "${PROJECT_SOURCE_DIR}/base/toys_utils.h"
    "${PROJECT_SOURCE_DIR}/base/toys_utils.h"
    "${PROJECT_SOURCE_DIR}/base/time.c"
    "${PROJECT_SOURCE_DIR}/base/time.h"
    "${PROJECT_SOURCE_DIR}/base/minunit.h"
    "${PROJECT_SOURCE_DIR}/base/vec.h"
    "${PROJECT_SOURCE_DIR}/base/vec.c"
    "${PROJECT_SOURCE_DIR}/base/mutex.c"
    "${PROJECT_SOURCE_DIR}/base/mutex.h"
    # 以下是echo_server
    "${PROJECT_SOURCE_DIR}/echo_server/echo_client.h"
    "${PROJECT_SOURCE_DIR}/echo_server/echo_client.c"
    "${PROJECT_SOURCE_DIR}/echo_server/echo_server.c"
    "${PROJECT_SOURCE_DIR}/echo_server/server.h"
    )
