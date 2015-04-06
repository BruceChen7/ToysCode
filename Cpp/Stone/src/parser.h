#ifndef __STONE__PARSER_H__
#define __STONE__PARSER_H__
#include "lexical.h"
#include <memory>
using namespace Stone;


namespace Stone
{
    class Parser
    {
        public:

            Parser(Lexical *lex):lex_(std::unique_ptr<Lexical>(lex)),total_token_num_{lex_->get_token_num()},parsed_token_num_{0}
            {
            
                lex->parse();
            }

            Parser(const Parser& ) = delete;
            Parser& operator = (const Parser&) = delete;
            void parse(); 
            static std::vector<Code_Token_Type> first_program_set_;
            static std::vector<Code_Token_Type> first_statement_set_;
            static std::vector<Code_Token_Type> first_simple_set_;
            static std::vector<Code_Token_Type> first_block_set_;
            static std::vector<Code_Token_Type> first_expr_set_;
            static std::vector<Code_Token_Type> first_factor_set_;
            static std::vector<Code_Token_Type> first_primary_set_;

            bool is_belonged_to_first_set(std::vector<Code_Token_Type>& set,Code_Token_Type type);
            ~Parser() = default;

        private:

            std::unique_ptr<Lexical> lex_; 

            int parsed_token_num_; 
            size_t total_token_num_;
            //parse  non-terminals
            bool parse_program();
            bool parse_statement();
            bool parse_operation();
            bool parse_simple();
            bool parse_block();
            bool parse_expr();
            bool parse_factor();
            bool parse_primary(); 
    };


} 

#endif
