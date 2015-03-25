#ifndef __STONE__PARSER_H__
#define __STONE__PARSER_H__
#include "lexical.h"
#include "stone_ast.h"
#include <functional>
#include <memory>
#include <stdio.h>
using namespace Stone;
using namespace Ast;

#define LOG(_token,_line_num) do \
{                              \
    fprintf(stderr,"Syntax Error :::::::: The Symbol is '%s' :::::: In Line ::::: %d\n",_token,_line_num);   \
}while(0)



namespace Stone
{
    class Parser
    {
        public:
            using TypeSet = std::vector<Code_Token_Type>;
            Parser(Lexical *lex);
            struct Token* get_token_to_be_parsed();
            void parse(); 
            ~Parser();

        private:
            //member
            std::unique_ptr<Lexical> lex_; 
            int total_token_num_;
            int cur_parsed_token_pos_; 
            struct Token* current_token_;
            std::vector<AstProgram::Ptr> program_; 
            bool err_state_;
            bool success_flag_;

            static std::vector<Code_Token_Type>program_first_set_; 
            static std::vector<Code_Token_Type>statement_first_set_;
            static std::vector<Code_Token_Type>simple_first_set_ ; 
            static std::vector<Code_Token_Type>block_first_set_ ; 
            static std::vector<Code_Token_Type>factor_first_set_ ;
            static std::vector<Code_Token_Type>Primary_first_set_ ;

            AstProgram::Ptr parse_program();
            AstStatement::Ptr parse_statement();
            AstSimple::Ptr parse_simple();
            AstExpr::Ptr parse_expr();
            AstFactor::Ptr parse_factor();
            AstOperation::Ptr parse_operation(); 
            AstBlock::Ptr parse_block();
            AstPrimary::Ptr parse_primary(); 

            // utils
            void token_has_parsed(); 
            bool is_token_eol_or_semi(struct Token* token);
            bool is_in_first_set(std::vector<Code_Token_Type>&,Code_Token_Type type)const; 
            //set the parsed token position in 
            void set_token_parsed_pos(int parsed_pos);
    };

    class ProgramParser
    {


    };

    class StatementParser
    {


    };

} 

#endif
