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

void AstIdentifier::accept(AstVisitor* visitor)
{ 
	visitor->visit(this);

}

AstString::AstString(struct Token* token):AstLeafNode(token)
{

}

void AstString::accept(AstVisitor* visitor)
{
	visitor->visit(this);
}

AstNumber::AstNumber(struct Token *token):AstLeafNode(token)
{

}

void AstNumber::accept(AstVisitor* visitor)
{
	visitor->visit(this); 
}

AstPrimary::AstPrimary(AstLeafNode *node):expr_node_(nullptr),leaf_node_(std::shared_ptr<AstLeafNode>(node))
{ 

}

AstPrimary::AstPrimary(AstExpr::Ptr node):expr_node_(node),leaf_node_(nullptr)
{

}

AstProgram::AstProgram():statement_{}
{

}
void AstProgram::add_statement(AstStatement::Ptr node)
{
	statement_.push_back(node);
	
}
