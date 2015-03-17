#include "../lexical.h"
#define CATCH_CONFIG_MAIN 
#include "../../../catch.hpp"
using namespace Stone;

TEST_CASE("File Unit Test && Lexical Unit test")
{
    SECTION("File Class Unit Test")
    {
        std::unique_ptr<File> source_file(new File("while.st"));
        source_file->read2buffer();
        REQUIRE(*(source_file->get_line(0))=="event = 0\n");
        REQUIRE(*(source_file->get_line(1))== "odd = 0\n");
        REQUIRE(*(source_file->get_line(2))== "while i < 10 {\n");
    }
    
    SECTION("Lexical Class Unit Test -- while.st")
    {
        std::unique_ptr<Lexical> lex(new Lexical("while.st"));
        lex->parse();
        REQUIRE(lex->get_token_info(0)->type == Code_Token_Type::Identifier); 
        REQUIRE(lex->get_token_info(1)->type == Code_Token_Type::Assgin);
        REQUIRE(lex->get_token_info(2)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(3)->type == Code_Token_Type::Eol);
        REQUIRE(lex->get_token_info(4)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(5)->type == Code_Token_Type::Assgin);
        REQUIRE(lex->get_token_info(6)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(7)->type == Code_Token_Type::Eol);
        REQUIRE(lex->get_token_info(8)->type == Code_Token_Type::While);
        REQUIRE(lex->get_token_info(9)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(10)->type == Code_Token_Type::LT);
        REQUIRE(lex->get_token_info(11)->type == Code_Token_Type::Integer); 
        REQUIRE(lex->get_token_info(12)->type == Code_Token_Type::LBRACE);
        REQUIRE(lex->get_token_info(13)->type == Code_Token_Type::Eol);
        REQUIRE(lex->get_token_info(14)->type == Code_Token_Type::If);
        REQUIRE(lex->get_token_info(15)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(16)->type == Code_Token_Type::Mod);
        REQUIRE(lex->get_token_info(17)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(18)->type == Code_Token_Type::EQ);
        REQUIRE(lex->get_token_info(19)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(20)->type == Code_Token_Type::LBRACE);
        REQUIRE(lex->get_token_info(21)->type == Code_Token_Type::Eol);
        REQUIRE(lex->get_token_info(22)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(23)->type == Code_Token_Type::Assgin);
        REQUIRE(lex->get_token_info(24)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(25)->type == Code_Token_Type::Add);
        REQUIRE(lex->get_token_info(26)->type == Code_Token_Type::Identifier);
        
    }

    SECTION("Assgin Lexical Uint Test --assign.st")
    {
        auto lex1 = std::unique_ptr<Lexical>(new Lexical("assign.st"));
        lex1->parse();
        REQUIRE(lex1->get_token_info(0)->type == Code_Token_Type::Identifier);
        REQUIRE(lex1->get_token_info(1)->type == Code_Token_Type::Assgin);
        REQUIRE(lex1->get_token_info(2)->type == Code_Token_Type::Integer);
        REQUIRE(lex1->get_token_info(3)->type == Code_Token_Type::Eol);
        REQUIRE(lex1->get_token_info(4)->type == Code_Token_Type::Eof); 

        REQUIRE(lex1->get_token_info(0)->value == "event");
        REQUIRE(lex1->get_token_info(1)->value == "=");
    }

    SECTION("Semicolon Lexical Uint Test --empty.st")
    {
        auto lex = std::unique_ptr<Lexical>(new Lexical("empty.st"));
        lex->parse();
        REQUIRE(lex->get_token_info(0)->type == Code_Token_Type::Semicolon);
        REQUIRE(lex->get_token_info(1)->type == Code_Token_Type::Eol);
        REQUIRE(lex->get_token_info(2)->type == Code_Token_Type::Identifier);
        REQUIRE(lex->get_token_info(3)->type == Code_Token_Type::Assgin);
        REQUIRE(lex->get_token_info(4)->type == Code_Token_Type::Integer);
        REQUIRE(lex->get_token_info(5)->type == Code_Token_Type::Semicolon);
    }

}


