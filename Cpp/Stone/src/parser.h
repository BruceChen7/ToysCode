#ifndef __STONE__PARSER_H__
#define __STONE__PARSER_H__
#include "lexical.h"
#include "stone_ast.h"
#include <memory>
#include <stdio.h>
using namespace Stone;
using namespace Ast;

#define LOG(_msg,_line_num) do \
{                              \
	fprintf(stderr,"%s:%d",_msg,_line_num);   \
}while(0)



namespace Stone
{
	enum class NodeType
	{
		Number,
		String,
		While,
		If,
		Identifier, 
	};

	
	class Parser
	{
		public:
			Parser(Lexical *lex);
			AstProgram::Ptr parse_program();
			AstNode::Ptr parse_statement();
			AstNode::Ptr parse_simple();
			AstExpr::Ptr parse_expr();
			AstNode::Ptr parse_factor();
			AstNode::Ptr parse_operation(); 
			AstNode::Ptr parse_block();
			AstPrimary::Ptr parse_primary(); 
			struct Token* get_next_token();

		private:
			std::shared_ptr<Lexical> lex_; 
			int parserd_token_num_;

	};
}


#endif
