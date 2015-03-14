#include "../parser.h"
#define CATCH_CONFIG_MAIN 
#include "../../../catch.hpp"
#include <memory.h>
using namespace Stone;

TEST_CASE("Parser Unit Test")
{
    

    auto lex = new Lexical("while.st"); 
    auto lex1 = new Lexical("assign.st");
    SECTION("Lexical Unit Test")
    {
        lex->parse();
        REQUIRE(lex->get_token_info(0)->type == Code_Token_Type::Identifier); 
        REQUIRE(lex->get_token_info(1)->type == Code_Token_Type::Assgin);
        REQUIRE(lex->get_token_info(2)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(3)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(4)->type == Code_Token_Type::Assgin);
        REQUIRE(lex->get_token_info(5)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(6)->type == Code_Token_Type::While);
        REQUIRE(lex->get_token_info(7)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(8)->type == Code_Token_Type::LT);
        REQUIRE(lex->get_token_info(9)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(10)->type == Code_Token_Type::LBRACE);
    }

    SECTION("Parser Unit Test")
    { 
        auto parser = std::make_shared<class Parser> (lex);
        REQUIRE(parser->get_next_token()->type == Code_Token_Type::Identifier); 
        REQUIRE(parser->parse_program() == nullptr);
    }

    SECTION("Parser Unit Test")
    {
        auto parser = std::make_shared<Parser>(lex1); 
        REQUIRE(parser->get_next_token()->type == Code_Token_Type::Identifier); 
        REQUIRE(parser->parse_program() == nullptr); 
    }

    

    
}



