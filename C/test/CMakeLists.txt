add_executable(test_toys_sds test_toys_sds.c)
target_link_libraries(test_toys_sds Toys_C_CODE  check_pic rt m pthread)
