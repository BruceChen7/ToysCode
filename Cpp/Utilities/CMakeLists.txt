add_subdirectory(test)
add_subdirectory(src)

enable_testing()
add_test(NAME get_first_follow_test COMMAND get_first_follow_test)
add_test(NAME log_unit_test COMMAND logTest)
