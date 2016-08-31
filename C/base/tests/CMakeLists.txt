add_executable(test_toys_sds test_toys_sds.c)
target_link_libraries(test_toys_sds base)

add_executable(test_toys_list test_toys_list.c)
target_link_libraries(test_toys_list base)

add_executable(test_toys_sort test_sort.c)
target_link_libraries(test_toys_sort base)