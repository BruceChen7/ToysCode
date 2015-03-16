#include "parser.h"
#include "lexical.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
using namespace Stone; 
using namespace Ast;


Parser::TypeSet Parser::program_first_set_ = { 
                Code_Token_Type::If,
                Code_Token_Type::While,
                Code_Token_Type::Minus, 
                Code_Token_Type::LBrackets,
                Code_Token_Type::Integer,
                Code_Token_Type::Identifier,
                Code_Token_Type::String,
                Code_Token_Type::Eol,
                Code_Token_Type::Semicolon 
};

Parser::TypeSet Parser::statement_first_set_ = {
    Code_Token_Type::If,
    Code_Token_Type::While,
    Code_Token_Type::Minus, 
    Code_Token_Type::LBrackets,
    Code_Token_Type::Integer,
    Code_Token_Type::Identifier,
    Code_Token_Type::String 
};

Parser::TypeSet Parser::simple_first_set_ = {
    Code_Token_Type::Minus, 
    Code_Token_Type::LBrackets,
    Code_Token_Type::Integer,
    Code_Token_Type::Identifier,
    Code_Token_Type::String,
};

Parser::TypeSet Parser::block_first_set_ = {
    Code_Token_Type::LBRACE 
};

Parser::TypeSet Parser::factor_first_set_ = {
    Code_Token_Type::Minus, 
    Code_Token_Type::LBrackets,
    Code_Token_Type::Integer,
    Code_Token_Type::Identifier,
    Code_Token_Type::String, 
}; 

Parser::TypeSet Parser::Primary_first_set_ {
    Code_Token_Type::LBrackets,
    Code_Token_Type::Integer,
    Code_Token_Type::Identifier,
    Code_Token_Type::String, 
};

Parser::Parser(Lexical* lex):lex_(std::unique_ptr<Lexical>(lex)),cur_parsed_token_pos_(0) 
{ 
    lex_->parse();
    total_token_num_ = lex_->get_token_num();
    program_.reserve(128);
}

struct Token*  Parser::get_token_to_be_parsed()
{ 
    assert(cur_parsed_token_pos_ < total_token_num_);
    current_token_ = lex_->get_token_info(cur_parsed_token_pos_);
    return current_token_;
}

void Parser::token_has_parsed()
{ 
    cur_parsed_token_pos_++;
}

AstPrimary::Ptr Parser::parse_primary()
{
    auto token = get_token_to_be_parsed();
    
    if(token->type == Code_Token_Type::LBrackets)
    {
        AstExpr::Ptr expr_node = parse_expr();

        if(expr_node == nullptr)
        {
            LOG("Syntax Error",token->line_num);
            return nullptr;
        } 
        else 
        {
             token_has_parsed();
             token = get_token_to_be_parsed();

             if(token->type == Code_Token_Type::RBrackets)
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

                    std::cout << "the ptoken is " << token->value << std::endl;

                    auto new_ast_identifier_node  =  new AstIdentifier(token);
                    new_primary_node  = new AstPrimary(new_ast_identifier_node); 

                    token_has_parsed(); 
                    token = get_token_to_be_parsed();

                    std::cout << "the next token is " << token->value << std::endl;

                    break;
                }

                case Code_Token_Type::Integer: 
                {
                    auto new_ast_number_node  =  new AstNumber(token);
                    new_primary_node  = new AstPrimary(new_ast_number_node); 

                    token_has_parsed();

                    token = get_token_to_be_parsed();

                    std::cout << "the next token is " << (int)token->type << std::endl;

  
                    break;
                }

                case Code_Token_Type::String:
                {
                    auto new_ast_string_node = new AstString(token);
                    new_primary_node = new AstPrimary(new_ast_string_node);
                    token_has_parsed();
                    break;
                }
                default:
                {
                    LOG("Syntax",token->line_num);
                }
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
    struct Token* token = get_token_to_be_parsed();
    std::cout << "the token is " << token->value << std::endl;
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
        std::cout << "Enter In Parse Primary " << std::endl;
        new_primary_node = parse_primary();
        
        if(new_primary_node == nullptr) 
            goto Err;
        else 
        {
            new_factor_node = std::shared_ptr<AstFactor>(new AstFactor(nullptr,new_primary_node)); 
        }
    }
    return new_factor_node;

    Err: 
        LOG("Syntax Error In Line",token->line_num); 
        return nullptr;
}

AstOperation::Ptr Parser::parse_operation()
{
    auto token = get_token_to_be_parsed();

    std::cout << "Enter In parse Operation" << std::endl;
    std::cout << "ther current operator is " << token->value << std::endl;
    
    if(token->type == Code_Token_Type::LBRACE)
        parse_block(true); 

    if(token->type == Code_Token_Type::Sub || token->type == Code_Token_Type::Add 
                                || token->type == Code_Token_Type::Mul || token->type == Code_Token_Type::Div
                                || token->type == Code_Token_Type::Assgin || token->type == Code_Token_Type::EQ 
                                || token->type == Code_Token_Type::LT || token->type == Code_Token_Type::LE
                                || token->type == Code_Token_Type::GE || token->type == Code_Token_Type::GT) 
    {
        auto new_operation_node = std::shared_ptr<AstOperation>(new AstOperation(token));
        assert(new_operation_node != nullptr);
        token_has_parsed();
        token = get_token_to_be_parsed();
        std::cout << "the next token is " << token->value << std::endl;
        return new_operation_node; 
    } 
    else 
    {
        LOG("Syntax Error In Parsing Operation",token->line_num);
        return nullptr;
    }
  
}

AstExpr::Ptr  Parser::parse_expr()
{
    std::cout << "Enter In Parse Expr" << std::endl;
    auto new_factor_node = parse_factor(); 
    AstExpr::Ptr new_expr_node;

    if(new_factor_node == nullptr)
        return nullptr;
    else 
    {
        new_expr_node = std::shared_ptr<AstExpr>(new AstExpr(new_factor_node)); 
        std::cout << "Enter In parse Expr Again" << std::endl;
    }


    while(1)
    {
        if(current_token_->type == Code_Token_Type::Eol)
        { 
            
            break;
        }
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

AstBlock::Ptr Parser::parse_block(bool must_be_a_block) 
{
    auto token =  get_token_to_be_parsed(); 
    auto new_block_node = std::shared_ptr<AstBlock>(new AstBlock());

    if(token->type == Code_Token_Type::LBRACE) 
    { 
        token_has_parsed();
        auto token_pos = cur_parsed_token_pos_;

        auto new_statement_node = parse_statement(false); 
        
        if(new_statement_node == nullptr)
            cur_parsed_token_pos_ = token_pos;
        else 
            new_block_node->add_statement(new_statement_node); 

        while(1)
        {
            token = get_token_to_be_parsed(); 

            if(token->type == Code_Token_Type::Semicolon || token->type == Code_Token_Type::Eof)
            { 
                token_pos = cur_parsed_token_pos_;
                auto new_other_statement_node = parse_statement(false); 

                if(new_other_statement_node == nullptr)
                {
                    cur_parsed_token_pos_ = token_pos;
                    break;
                }
                else 
                    new_block_node->add_statement(new_other_statement_node); 
            } 
            else 
                goto Err; 
        } 
        token = get_token_to_be_parsed();

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
        if(must_be_a_block)
            LOG("Syntax Error In Parsing Block ",token->line_num); 
            return nullptr; 
}

AstSimple::Ptr Parser::parse_simple()
{ 
    std::cout << "Enter In Parse Simple" << std::endl;
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


AstStatement::Ptr Parser::parse_statement(bool must_be_a_statement)
{
    auto token = get_token_to_be_parsed();
    auto token_pos = cur_parsed_token_pos_;
    auto value = (token->value).data(); 

    AstStatement::Ptr new_statement_node = nullptr;
    AstExpr::Ptr new_expr_node = nullptr;
    AstSimple::Ptr new_simple_node = nullptr;
    AstBlock::Ptr new_block_node = nullptr;
    AstLeafNode::Ptr new_if_node = nullptr;
    AstLeafNode::Ptr new_else_node = nullptr;
    AstBlock::Ptr new_else_block_node = nullptr;

    std::cout << "enter in Pase statment"<< std::endl;

    if(token->type == Code_Token_Type::If)
    { 
        new_if_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token));
        new_expr_node = parse_expr(); 
        
        if(new_expr_node == nullptr)
            goto Err;
        else 
        {
            new_block_node = parse_block(true);

            if(new_block_node == nullptr)
            {
                goto Err;
            }
            else
            {
                 token = get_token_to_be_parsed();
                 value = token->value.data();

                if((::strcmp(value,"else")==0) && (new_else_block_node =  parse_block(true) ) != nullptr)
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
    else if(current_token_->type == Code_Token_Type::While)  
    {
        token_has_parsed();

        if((new_expr_node = parse_expr()) != nullptr && (new_block_node = parse_block(true))!= nullptr)
        {
            auto new_while_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token)); 
            new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_while_node,new_expr_node,new_block_node)); 
        }
    }
    else 
    { 
        new_simple_node = parse_simple(); 

        if(new_simple_node == nullptr)
            goto Err; 
        else 
        { 
            new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_simple_node)); 
            assert(new_statement_node != nullptr);
        }
    } 

    Err: 
        if(must_be_a_statement)
        {
            LOG("Syntax Error In Parsing Statement \n",token->line_num); 
            return new_statement_node;
        }
     return new_statement_node;
}

AstProgram::Ptr Parser::parse_program()
{
    auto token = get_token_to_be_parsed();

    switch(token->type)
    {
        case Code_Token_Type::Eol:
            token_has_parsed();
            break;
        case Code_Token_Type::Semicolon:
            token_has_parsed();
            break;

        case Code_Token_Type::Eof:
            return nullptr;

        default: 
            break; 
    }

    AstProgram* new_ast_program_node = new AstProgram();

    auto new_ast_statement_node = parse_statement(true); 
        
    if(new_ast_statement_node != nullptr)
    { 
        new_ast_program_node->add_statement(new_ast_statement_node);
        return std::shared_ptr<AstProgram>(new_ast_program_node);
    }

    else 
    {
        LOG("Syntax Error In Parsing Programe: ",current_token_->line_num); 
        return nullptr;
    } 

    return nullptr;
}

void Parser::parse()
{ 
          
    AstProgram::Ptr ptr = nullptr;

    while(cur_parsed_token_pos_< total_token_num_)
    {
        
        auto token = get_token_to_be_parsed();

        if(token->type != Code_Token_Type::Eof)
        {
            if((ptr = parse_program()) != nullptr )
            {
                program_.push_back(ptr); 
            }
            else 
            {
                ::fprintf(stderr,"Error In Parse Your file");
                break;
            }
        }
        else 
            break;
    }

}
