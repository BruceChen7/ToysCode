#include <Stone/src/parser.h>
#include <Stone/src/stone_ast.h>
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include <memory.h>
using namespace Stone;

TEST_CASE("Parser Unit Test")
{
    auto parser = std::unique_ptr<Parser>(new Parser(new Lexical("while.st")));

    parser->parse();

}



