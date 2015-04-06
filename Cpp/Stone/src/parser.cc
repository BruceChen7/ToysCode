#include "parser.h"
#include "lexical.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace Stone; 


std::vector<Code_Token_Type> Parser::first_program_set_ = {
	Code_Token_Type::Semicolon,
	Code_Token_Type::Eol,
	Code_Token_Type::If,
	Code_Token_Type::While,
	Code_Token_Type::Minus,
	Code_Token_Type::LBrackets,
	Code_Token_Type::Integer,
	Code_Token_Type::Identifier,
	Code_Token_Type::String 
};


std::vector<Code_Token_Type> Parser::first_statement_set_ = { 
	Code_Token_Type::If,
	Code_Token_Type::While,
	Code_Token_Type::Minus,
	Code_Token_Type::LBrackets,
	Code_Token_Type::Integer,
	Code_Token_Type::Identifier,
	Code_Token_Type::String 
};

std::vector<Code_Token_Type> Parser::first_simple_set_ = {
	Code_Token_Type::Minus,
	Code_Token_Type::LBrackets,
	Code_Token_Type::Integer,
	Code_Token_Type::Identifier,
	Code_Token_Type::String 

};

std::vector<Code_Token_Type> Parser::first_block_set_ = {
	Code_Token_Type::LBRACE 
};

std::vector<Code_Token_Type> Parser::first_expr_set_ = {
	Code_Token_Type::If,
	Code_Token_Type::While,
	Code_Token_Type::Minus,
	Code_Token_Type::LBrackets,
	Code_Token_Type::Integer,
	Code_Token_Type::Identifier,
	Code_Token_Type::String 
};

std::vector<Code_Token_Type> Parser::first_factor_set_ = {
	Code_Token_Type::Minus,
	Code_Token_Type::LBrackets,
	Code_Token_Type::Integer,
	Code_Token_Type::Identifier,
	Code_Token_Type::String 

};

std::vector<Code_Token_Type> Parser::first_primary_set_ = {
	Code_Token_Type::LBRACE,
	Code_Token_Type::Integer,
	Code_Token_Type::String,
	Code_Token_Type::Identifier,
	Code_Token_Type::Integer 
};

bool is_belonged_to_first_set(std::vector<Code_Token_Type>& set,Code_Token_Type type)
{
    for(auto  elem : set)
    {
        if(elem  ==  type) 
            return true;
    }
    return false;

}


void Parser::parse()
{


}

bool Parser::parse_program()
{
	auto token = lex_->get_token_info(parsed_token_num_);
	auto parsed_flag = false;

	if(!is_belonged_to_first_set(first_program_set_,token->type))
		return false;
	
	switch(token->type)
	{
		case Code_Token_Type::Semicolon:
		case Code_Token_Type::Eol:
			parsed_token_num_++; 
			parsed_flag = true;
			break;
		default: 
			parsed_flag = parse_statement();
	
	} 

    return parsed_flag;
}

bool Parser::parse_statement()
{
	auto token = lex_->get_token_info(parsed_token_num_);
	auto parsed_flag = false;

	switch(token->type)
	{
		case Code_Token_Type::If:
			//'if' has been accepted
			parsed_token_num_++;

			parsed_flag = parse_expr();

			if(parsed_flag)
			{
				parsed_flag = parse_block(); 

				if(parsed_flag)
				{ 
					token = lex_->get_token_info(parsed_token_num_);

					if(::strcmp(token->value.data(),"else"))
					{
						parsed_token_num_ ++; 
						parsed_flag = parse_block(); 
					} 
				} 
			} 
			break;

		case Code_Token_Type::While: 
			//'while' has been accepted;
			parsed_token_num_++;
			
			parsed_flag = parse_expr();
			
			if(parsed_flag)
			{ 
				parsed_flag = parse_block();
			}
			
			break;

		default: 
			parsed_flag = parse_simple(); 
	}
	return parsed_flag; 
}


bool Parser::parse_simple()
{
	auto token = lex_->get_token_info(parsed_token_num_);

	if(!is_belonged_to_first_set(first_simple_set_,token->type))
		return false; 

	auto parsed_flag = parse_expr(); 
    return parsed_flag;
}


bool Parser::parse_expr()
{ 
	auto token = lex_->get_token_info(parsed_token_num_);

	if(!is_belonged_to_first_set(first_expr_set_,token->type))
		return false; 

	auto parsed_flag = parse_factor(); 
	
	while(parsed_flag)
	{
		auto reserved_parsed_num = parsed_token_num_; 

		if(parse_operation())
		{
			if(!parse_factor())
			{
				parsed_flag = false;
				break;
			}
			//OP factor
			else 
			{
				continue;
			}
			
		}
		else 
		{
			parsed_token_num_ = reserved_parsed_num;
			break;
		}
	} 
	return parsed_flag;
}


bool Parser::parse_factor()
{
	auto token = lex_->get_token_info(parsed_token_num_);

	if(!is_belonged_to_first_set(first_factor_set_,token->type))
		return false;

	auto parsed_flag = false;

	switch(token->type)
	{
		case Code_Token_Type::Minus:
			parsed_token_num_++;
			parsed_flag = parse_primary();
			break; 
		default: 
			parsed_flag = parse_primary(); 
	}

    return parsed_flag;
}

bool Parser::parse_primary()
{
	auto token = lex_->get_token_info(parsed_token_num_);

	if(!is_belonged_to_first_set(first_primary_set_,token->type))
		return false;

	auto parsed_flag = false;
	
	switch(token->type)
	{
		case Code_Token_Type::LBrackets:
			parsed_token_num_ ++;
			parsed_flag = parse_expr();

			if(parsed_flag)
			{
				token = lex_->get_token_info(parsed_token_num_); 

				if(token->type == Code_Token_Type::RBrackets)
				{
					parsed_token_num_ ++; 
					parsed_flag = true;
					break;
				} 
				else 
				{
					parsed_flag = false;
					break;
				}
			}
			else 
				break;

		case Code_Token_Type::Integer:
			parsed_flag = true;
			parsed_token_num_++;

		case Code_Token_Type::Identifier:
			parsed_flag = true;
			parsed_token_num_++;

		case Code_Token_Type::String:
			parsed_flag = true;
			parsed_token_num_++;

		default:
			break;
	} 
    return parsed_flag ;
}


