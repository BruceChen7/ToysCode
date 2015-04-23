#ifndef __STONE__PARSER_H__
#define __STONE__PARSER_H__

#include <Stone/src/lexical.h>
#include <memory>
using namespace Stone;

#define LOG(_token,_line,_msg,_flag) do{   \
    if(!_flag)                             \
    {                                      \
        _flag = true;                      \
        ::fprintf(stderr,"Syntax Error:::::: %s ::::::  In Line :::: %d ::::%s \n",_token,_line,_msg);\
    }\
}while(0)


namespace Stone
{
    class Parser
    {
        public:

            Parser(Lexical *lex):lex_(std::unique_ptr<Lexical>(lex)),parsed_token_num_{0},is_set_err_flag_(false),parse_success_flag_(false)
            {
            
                lex_->parse();
                total_token_num_ = lex_->get_token_num();
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
            bool is_set_err_flag_;
            bool parse_success_flag_;

            //parse  terminals and non-terminals 
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
