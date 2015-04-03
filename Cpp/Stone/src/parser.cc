#include "parser.h"
#include "lexical.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace Stone; 



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
    

    return false;
}

bool Parser::parse_statement()
{

    return false;

}


bool Parser::parse_simple()
{

    return false;
}


bool Parser::parse_expr()
{

    return false;

}


bool Parser::parse_factor()
{


    return false;
}

bool Parser_primary()
{

    return false;
}


