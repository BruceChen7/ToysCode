add_subdirectory(Src)
add_subdirectory(Test)

enable_testing()
add_test(NAME lexical_unit_test COMMAND lexical_unit_test)

