#include "parser.h"
#include "lexical.h"
#include <string.h>
using namespace Stone;
using namespace Ast;

Parser::Parser(Lexical* lex):lex_(std::make_shared<Lexical>(*lex)),parserd_token_num_(0)
{ 

}

struct Token* Parser::get_next_token()
{ 
	auto p_token = lex_->get_token_info(parserd_token_num_);
	parserd_token_num_++;
	return p_token;
}

AstNode::Ptr Parser::parse_program()
{ 
	auto token = get_next_token();
	return nullptr;
}

AstNode::Ptr Parser::parse_primary()
{
	auto token = get_next_token();
	auto ptr = token->value.data();

	if(::strcmp(ptr,"(") == 0)
	{
		auto expr_node = parse_expr();

		if(expr_node == nullptr)
		{
			LOG("Sytax Error",token->line_num);
			return nullptr;
		}

		else 
		{
			 token = get_next_token();
			 ptr = token->value.data();

			 if(::strcmp(ptr,")") == 0)
			 {
			 	
			 
			 }
			 else 
			 {
				LOG("Sytax Error",token->line_num);
				return nullptr;
			 
			 }
		}

	}
	else
	{
		if(token->type == Code_Token_Type::Identifier || token->type ==  Code_Token_Type::Integer || token->type == Code_Token_Type::String)
		{
			
		
		}
	
	}
		

}

AstNode::Ptr Parser::parse_factor()
{
	struct Token* token = get_next_token();
	
	if(::strcmp((token->value).data(),"-")) 
	{
	}
	return nullptr;
}

AstNode::Ptr  Parser::parse_expr()
{
	return nullptr;
}

AstNode::Ptr Parser::parse_block() 
{

	return nullptr;
}

