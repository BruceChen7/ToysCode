add_executable(test_binary_tree  test_binary_tree.c)
target_link_libraries(test_binary_tree  DS criterion)

add_executable(test_string test_string.c)
target_link_libraries(test_string  DS criterion)

add_executable(test_queue test_queue.c)
target_link_libraries(test_queue DS criterion)
