#include "parser.h"
#include "lexical.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
using namespace Stone;
using namespace Ast;

Parser::Parser(Lexical* lex):lex_(std::unique_ptr<Lexical>(lex)),parsed_token_num_(0)
{ 

}

struct Token* Parser::get_next_token()
{ 

    auto token_num = lex_->get_token_num();
    assert(parsed_token_num_ <= token_num);
    auto p_token = lex_->get_token_info(parsed_token_num_);
    parsed_token_num_++;
    return p_token;
}


AstPrimary::Ptr Parser::parse_primary()
{
    auto token = get_next_token();

    if(token->type == Code_Token_Type::LBRACE)
    {
        AstExpr::Ptr expr_node = parse_expr();

        if(expr_node == nullptr)
        {
            LOG("Syntax Error",token->line_num);
            return nullptr;
        } 
        else 
        {
             token = get_next_token();

             if(token->type == Code_Token_Type::RBRACE)
             {

                auto new_primary_node = new AstPrimary(expr_node);
                return std::shared_ptr<AstPrimary>(new_primary_node);
             }
             else 
             {
                LOG("Syntax Error",token->line_num);
                return nullptr;
             
             }
        }

    }
    else
    {
        AstPrimary *new_primary_node = nullptr;


        if(token->type == Code_Token_Type::Identifier || token->type ==  Code_Token_Type::Integer || token->type == Code_Token_Type::String)
        {
            switch(token->type)
            {
                case Code_Token_Type::Identifier:
                {

                    auto new_ast_identifier_node  =  new AstIdentifier(token);
                    new_primary_node  = new AstPrimary(new_ast_identifier_node); 
                    break;
                }

                case Code_Token_Type::Integer: 
                {
                    auto new_ast_number_node  =  new AstNumber(token);
                    new_primary_node  = new AstPrimary(new_ast_number_node); 
                    break;
                }

                case Code_Token_Type::String:
                {
                    auto new_ast_string_node = new AstString(token);
                    new_primary_node = new AstPrimary(new_ast_string_node);
                    break;
                }
                default:
                    break;
            } 
            return std::shared_ptr<AstPrimary>(new_primary_node);
        }
        else 
        {
            LOG("Syntax Error",token->line_num);
            return nullptr;
        }
    }
        

}



AstFactor::Ptr Parser::parse_factor()
{
    struct Token* token = get_next_token();
    AstPrimary::Ptr new_primary_node;
    AstFactor::Ptr new_factor_node;

    if(token->type == Code_Token_Type::Minus) 
    {
        auto new_minus_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token));
        new_primary_node = parse_primary();

        if(new_primary_node != nullptr)
        { 
            new_factor_node = std::shared_ptr<AstFactor>(new AstFactor(new_minus_node,new_primary_node)); 
        }   
        else
            goto Err;
    }
    else
    {
        new_primary_node = parse_primary();
        
        if(new_primary_node == nullptr) 
            goto Err;
        else 
            new_factor_node = std::shared_ptr<AstFactor>(new AstFactor(nullptr,new_primary_node)); 
    }
    return new_factor_node;

    Err: 
        LOG("Syntax Error In Line",token->line_num); 
        return nullptr;
}

AstOperation::Ptr Parser::parse_operation()
{
    auto token = get_next_token();

    if(token->type == Code_Token_Type::Sub || token->type == Code_Token_Type::Add 
                                || token->type == Code_Token_Type::Mul || token->type ==Code_Token_Type::Div) 
    {
        auto new_operation_node = std::shared_ptr<AstOperation>(new AstOperation(token));
        return new_operation_node; 
    } 
    else 
    {
        LOG("Syntax Error In Line",token->line_num);
        return nullptr;
    }
  
}

AstExpr::Ptr  Parser::parse_expr()
{
    auto new_factor_node = parse_factor(); 
    AstExpr::Ptr new_expr_node;

    if(new_factor_node == nullptr)
        return nullptr;
    else 
        new_expr_node = std::shared_ptr<AstExpr>(new AstExpr(new_factor_node));

    while(1)
    {
        auto new_operation_node = parse_operation();
        auto new_factor_node = parse_factor();

        if(new_operation_node != nullptr && new_factor_node != nullptr)
        { 
            new_expr_node->add_op_factor(new_operation_node,new_factor_node);
            continue;

        }
        else 
            break; 
    } 
    return new_expr_node; 
}

AstBlock::Ptr Parser::parse_block() 
{
    auto token =  get_next_token(); 
    auto new_block_node = std::shared_ptr<AstBlock>(new AstBlock());
    if(token->type == Code_Token_Type::LBRACE) 
    {

        auto token_pos = parsed_token_num_;
        auto new_statement_node = parse_statement(); 
        
        if(new_statement_node == nullptr)
            parsed_token_num_ = token_pos;
        else 
            new_block_node->add_statement(new_statement_node); 

        while(1)
        {
            token = get_next_token(); 

            if(token->type == Code_Token_Type::Semicolon || token->type == Code_Token_Type::Eof)
            { 
                token_pos = parsed_token_num_;
                auto new_other_statement_node = parse_statement(); 

                if(new_other_statement_node == nullptr)
                {
                    parsed_token_num_ = token_pos;
                    break;
                }
                else 
                    new_block_node->add_statement(new_other_statement_node); 
            } 
            else 
                goto Err; 
        } 
        token = get_next_token();

        if(token->type == Code_Token_Type::RBRACE)
        {
            return new_block_node;
        } 
        else 
            goto Err;
    }
    else 
        goto Err;

    Err:
        LOG("Syntax Error In Line :",token->line_num); 
        return nullptr; 
}

AstSimple::Ptr Parser::parse_simple()
{ 
    auto new_expr_node = parse_expr();

    if(new_expr_node != nullptr)
    {
        auto new_simple_node = std::shared_ptr<AstSimple>(new AstSimple(new_expr_node));
        return new_simple_node;
    }
    else 
    {
        return nullptr;
    }
    
}


AstStatement::Ptr Parser::parse_statement()
{
    auto token_pos = parsed_token_num_;
    auto token = get_next_token(); 
    auto value = token->value.data();

    AstStatement::Ptr new_statement_node = nullptr;
    AstExpr::Ptr new_expr_node = nullptr;
    AstSimple::Ptr new_simple_node = nullptr;
    AstBlock::Ptr new_block_node = nullptr;
    AstLeafNode::Ptr new_if_node = nullptr;
    AstLeafNode::Ptr new_else_node = nullptr;
    AstBlock::Ptr new_else_block_node = nullptr;

    if(::strcmp(value,"if") == 0)
    { 
        new_if_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token));
        new_expr_node = parse_expr(); 
        
        if(new_expr_node == nullptr)
            goto Err;
        else 
        {
            new_block_node = parse_block();

            if(new_block_node == nullptr)
            {
                goto Err;
            }
            else
            {
                 token = get_next_token();
                 value = token->value.data();

                if((::strcmp(value,"else")==0) && (new_else_block_node =  parse_block() ) != nullptr)
                {

                    new_else_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token));
                    new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_if_node,new_expr_node,
                                                                       new_block_node,new_else_node,new_else_block_node));
                
                } 
                else 
                {

                    new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_if_node,new_expr_node,new_block_node,nullptr,nullptr));
                }
            }
        } 
        return  new_statement_node;
    }
    else if(strcmp(value,"while") == 0 && (new_expr_node = parse_expr()) != nullptr && (new_block_node = parse_block()))
    {
        auto new_while_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token)); 
        new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_while_node,new_expr_node,new_block_node)); 
    }
    else 
    {
        new_simple_node = parse_simple(); 
        
        if(new_simple_node == nullptr)
            goto Err; 
        else 
            new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_simple_node)); 
        return new_statement_node;
    } 

    Err: 
        LOG("Syntax Error In Line",token->line_num); 
        return new_statement_node;
}

AstProgram::Ptr Parser::parse_program()
{
    //reserve origin parsed token position
    auto token_pos  = parsed_token_num_;
    AstProgram* new_ast_program_node = nullptr; 
    auto new_ast_statement_node = parse_statement(); 
        
    if(new_ast_statement_node != nullptr)
    {
            new_ast_program_node->add_statement(new_ast_statement_node);
    }
    else 
    {
        parsed_token_num_ = token_pos; 
    }

    struct Token *token = get_next_token();

    if(token->type == Code_Token_Type::Eof ||token->type == Code_Token_Type::Semicolon)
    {
        return std::shared_ptr<AstProgram>(new_ast_program_node);
    }
    else 
    {
        LOG("Syntax Error In Line : ",token->line_num); 
        return nullptr;
    } 

}
