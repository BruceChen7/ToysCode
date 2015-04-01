#ifndef __STONE__PARSER_H__
#define __STONE__PARSER_H__
#include "lexical.h"
#include "stone_ast.h"
#include <memory>
using namespace Stone;


namespace Stone
{
    class Parser
    {
        public:
            Parser(Lexical *lex, AstParser *parser):leaf_parser_(std::unique_ptr<AstParser>(parser))
                                                        ,lex_(std::unique_ptr<Lexical>(lex))
            {
            
            }


        private:
            std::unique_ptr<Lexical> lex_;
            std::unique_ptr<AstParser> leaf_parser_;

    };


} 

#endif
