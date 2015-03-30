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
    };


} 

#endif
