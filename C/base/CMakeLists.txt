cmake_minimum_required(VERSION 2.8)
project(TOYS_C C)

add_subdirectory(test)

set(Toy_C_SRC
	toys_sds.c
	toys_list.c
	toys_mem.c
    toys_skiplist.c
	)

add_library(Toys_C_CODE ${Toy_C_SRC})

enable_testing()
add_test(NAME sds_test COMMAND sds_test)
add_test(NAME list_test COMMAND list_test)

