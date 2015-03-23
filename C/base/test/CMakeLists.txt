add_executable(test_toys_sds test_toys_sds.c)
target_link_libraries(test_toys_sds Toys_C_CODE criterion)

add_executable(test_toys_list test_toys_list.c)
target_link_libraries(test_toys_list Toys_C_CODE  criterion)
