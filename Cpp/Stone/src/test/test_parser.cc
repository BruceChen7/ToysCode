#include "../parser.h"
#define CATCH_CONFIG_MAIN 
#include "../../../catch.hpp"
#include <memory.h>
using namespace Stone;

TEST_CASE("Parser Unit Test")
{

    auto assign_parser = std::unique_ptr<Parser>(new Parser(new Lexical("assign.st")));

    SECTION("Parser Unit Test -- assign.st")
    {

        assign_parser->parse();

    }

    SECTION("Parser Unit Test -- while.st")
    { 
    } 

}


