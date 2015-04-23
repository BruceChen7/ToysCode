
add_executable(test_lexical test_lexical.cc)
target_link_libraries(test_lexical STONE)

add_executable(test_parser test_parser.cc)
target_link_libraries(test_parser STONE)

add_executable(test_stone_ast test_stone_ast.cc)
target_link_libraries(test_stone_ast STONE)


