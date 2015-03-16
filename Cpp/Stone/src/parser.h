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
    fprintf(stderr,"%s:%d\n",_msg,_line_num);   \
}while(0)



namespace Stone
{
    class Parser
    {
        public:
            Parser(Lexical *lex);
            AstProgram::Ptr parse_program();
            AstStatement::Ptr parse_statement();
            AstSimple::Ptr parse_simple();
            AstExpr::Ptr parse_expr();
            AstFactor::Ptr parse_factor();
            AstOperation::Ptr parse_operation(); 
            AstBlock::Ptr parse_block();
            AstPrimary::Ptr parse_primary(); 
            struct Token* get_next_token();
            void parse(); 
        private:
            std::unique_ptr<Lexical> lex_; 
            int parsed_token_num_; 
            struct Token* current_token_;
            std::vector<AstProgram::Ptr> program_;
    };
} 

#endif
