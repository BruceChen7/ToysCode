#include "parser.h"
#include "stone_ast.h"
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include <memory.h>
using namespace Stone;

TEST_CASE("Parser Unit Test")
{
    auto lex = new Lexical("while.st");
    auto ast_leaf_parser  = new AstLeafParser();
    auto parser =  Parser(lex,ast_leaf_parser); 
}



