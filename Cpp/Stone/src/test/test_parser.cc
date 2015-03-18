#include "../parser.h"
#define CATCH_CONFIG_MAIN 
#include "../../../catch.hpp"
#include <memory.h>
using namespace Stone;

TEST_CASE("Parser Unit Test")
{

    auto assign_parser = std::unique_ptr<Parser>(new Parser(new Lexical("assign.st")));
    auto while_parser = std::unique_ptr<Parser>(new Parser(new Lexical("while.st")));
    // auto empty_parser = std::unique_ptr<Parser>(new Parser(new Lexical("empty.st")));

    SECTION("Parser Unit Test -- assign.st")
    {

        // assign_parser->parse();

    }

    SECTION("Parser Unit Test -- while.st")
    { 
        while_parser->parse();
    } 

    SECTION("Parser Empty Set -- empty.st")
    {
        // empty_parser->parse(); 
    }

}



