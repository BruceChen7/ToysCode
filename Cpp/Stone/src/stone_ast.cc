#include <Stone/src/stone_ast.h>
#include <Stone/src/lexical.h>
using namespace Stone;


bool AstParser::parse_ast_leaf(AstLeafNode* node, Code_Token_Type type)
{
    if(node->get_token()->type != type)
        return false;
    else 
    {
        char buf[64]; 
        err_line_num_ = node->get_token()->line_num; 
        ::snprintf(buf,sizeof(buf),"Sorry,%s is qualified in %d",node->get_token()->value.data(),err_line_num_);
        err_msg_ = std::string(buf); 
        return false ; 
    }
}

bool AstParser::visit(AstNumber *number)
{ 
   return parse_ast_leaf(number,Code_Token_Type::Integer);
}

bool AstParser::visit(AstString *str)
{ 
    return parse_ast_leaf(str,Code_Token_Type::String);
}

bool AstParser::visit(AstIdentifier *identifier) { 
    return parse_ast_leaf(identifier,Code_Token_Type::Identifier); 
}


bool AstParser::visit(AstOperation *operation)
{
    

}
