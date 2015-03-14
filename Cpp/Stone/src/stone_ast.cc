#include "stone_ast.h"
#include "lexical.h"
using namespace Stone;
using namespace Ast;

AstLeafNode::AstLeafNode(struct Token* token)
{

    type_ = token->type;
    value_ = token->value;
    line_num_ = token->line_num; 
}


void AstLeafNode::accept(AstVisitor *visitor)
{
    visitor->visit(this);
}

AstIdentifier::AstIdentifier(struct Token* token):AstLeafNode(token)
{ 
}

AstOperation::AstOperation(struct Token* token):AstLeafNode(token)
{

}

void AstIdentifier::accept(AstVisitor* visitor)
{ 
    visitor->visit(this);

}

AstString::AstString(struct Token* token):AstLeafNode(token)
{

}


AstNumber::AstNumber(struct Token *token):AstLeafNode(token)
{

}


AstExpr::AstExpr(AstFactor::Ptr node)
{
    
}
void AstExpr::add_op_factor(AstOperation::Ptr op,AstFactor::Ptr factor)
{
    AstExpr::AstOpFactor op_factor{op,factor}; 
    ast_op_factor_.push_back(op_factor);
}

AstPrimary::AstPrimary(AstLeafNode *node):expr_node_(nullptr),
                                         leaf_node_(std::shared_ptr<AstLeafNode>(node))
{ 

}

AstPrimary::AstPrimary(AstExpr::Ptr node):expr_node_(node)
                                          ,leaf_node_(nullptr)
{ 

}

void AstBlock::add_statement(AstStatement::Ptr statement)
{
    statement_.push_back(statement);
}

AstBlock::AstBlock()
{ 
    statement_.reserve(10);
}

AstSimple::AstSimple(AstExpr::Ptr expr):expr_(expr)
{

}

AstStatement::AstStatement(AstLeafNode::Ptr if_node,
                           AstExpr::Ptr expr,
                           AstBlock::Ptr if_block,
                           AstLeafNode::Ptr else_node,
                           AstBlock::Ptr else_block):if_statement_{if_node,expr,if_block,else_node,else_block},
                         while_stament_{nullptr,nullptr,nullptr},
                         simple_statement_{nullptr}

{ 
    

}

AstStatement::AstStatement(AstLeafNode::Ptr while_node,AstExpr::Ptr expr,AstBlock::Ptr block):
                                                    while_stament_{while_node,expr,block},
                                                    if_statement_{nullptr,nullptr,nullptr},
                                                    simple_statement_{nullptr}
{


}

AstStatement::AstStatement(AstSimple::Ptr simple):simple_statement_{simple},
                                                  if_statement_{nullptr,nullptr,nullptr},
                                                  while_stament_{nullptr,nullptr,nullptr}
{

}



AstProgram::AstProgram():statement_{} 
{

}
void AstProgram::add_statement(AstStatement::Ptr node)
{
    statement_.push_back(node);
    
}

void AstNumber::accept(AstVisitor* visitor)
{
    visitor->visit(this); 
}

void AstString::accept(AstVisitor* visitor)
{
    visitor->visit(this);
}
