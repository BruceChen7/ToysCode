#include "../parser.h"
#define CATCH_CONFIG_MAIN 
#include "../../../catch.hpp"
using namespace Stone;

TEST_CASE("Parser Unit")
{
	File* source_file = new File("while.st");
	source_file->read2buffer();
	REQUIRE(*(source_file->get_line(0))=="event = 0\n");
	REQUIRE(*(source_file->get_line(1))== "odd = 0\n");
	REQUIRE(*(source_file->get_line(2))== "while i < 10 {\n");
	
	Lexical* lex = new Lexical(source_file); 
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

	auto parser = std::make_shared<class Parser> (lex);
	REQUIRE(parser->get_next_token()->type == Code_Token_Type::Identifier); 
	delete lex;
}



