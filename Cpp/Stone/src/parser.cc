#include "parser.h"
#include "lexical.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
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

Parser::Parser(Lexical* lex):lex_(std::unique_ptr<Lexical>(lex)),cur_parsed_token_pos_(0),err_state_(0)
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

bool Parser::is_in_first_set(Parser::TypeSet& vec, Code_Token_Type type) const 
{
    for(const auto &elem : vec)
    {
        if(elem == type)
            return true;
    }
    return false;

}
void Parser::token_has_parsed()
{ 
    cur_parsed_token_pos_++;
}

bool Parser::is_token_eol_or_semi(struct Token* token)
{
    if(token->type == Code_Token_Type::Eol || token->type == Code_Token_Type::Semicolon)
        return true;
    else 
        return false;

}
void Parser::set_token_parsed_pos(int parsed_pos)
{
    cur_parsed_token_pos_ = parsed_pos;
}

AstPrimary::Ptr Parser::parse_primary()
{
    auto token = get_token_to_be_parsed();
    
    if(token->type == Code_Token_Type::LBrackets)
    {
        AstExpr::Ptr expr_node = parse_expr();

        if(expr_node == nullptr)
        {
            LOG(token->value.data(),token->line_num);
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
                LOG(token->value.c_str(),token->line_num);
                return nullptr;
             
             }
        }

    }
    else if(is_token_eol_or_semi(token))
            return nullptr; 
    else
    {
        AstPrimary *new_primary_node = nullptr; 
        
        if(token->type == Code_Token_Type::Identifier || token->type ==  Code_Token_Type::Integer || token->type == Code_Token_Type::String)
        {
            switch(token->type)
            {
                case Code_Token_Type::Identifier:
                {

                    std::cout << "the token is " << token->value << std::endl;

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
                    LOG(token->value.c_str(),token->line_num);
                }
            } 

            return std::shared_ptr<AstPrimary>(new_primary_node);
        }
        else 
        {
            LOG(token->value.data(),token->line_num);
            return nullptr;
        }
    }
        

}



AstFactor::Ptr Parser::parse_factor()
{
    std::cout << " Enter in parse factor " << std::endl;

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
        LOG(token->value.data(),token->line_num); 
        return nullptr;
}

AstOperation::Ptr Parser::parse_operation()
{
    auto token = get_token_to_be_parsed();

    std::cout << "Enter In parse Operation" << std::endl;
    std::cout << "ther current operator is " << token->value << std::endl;
    
    if(token->type == Code_Token_Type::LBRACE)
        parse_block(); 

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
    else if(is_token_eol_or_semi(token))
        return nullptr;
    else 
    {
        LOG(token->value.data(),token->line_num);
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

        if(current_token_->type == Code_Token_Type::Eol || current_token_->type == Code_Token_Type::LBRACE)
        { 
            break;
        }
        //restore the current token
        auto token = current_token_;
        auto cur_parsed_token_pos =  cur_parsed_token_pos_;

        auto new_operation_node = parse_operation();
        auto new_factor_node = parse_factor();

        if(new_operation_node != nullptr && new_factor_node != nullptr)
        { 
            new_expr_node->add_op_factor(new_operation_node,new_factor_node);
            //try more OP factor
            continue; 
        }
        else
        {
            set_token_parsed_pos(cur_parsed_token_pos); 
            break;
        }
            
    } 
    return new_expr_node; 
}

AstBlock::Ptr Parser::parse_block() 
{
    auto token =  get_token_to_be_parsed(); 
    auto new_block_node = std::shared_ptr<AstBlock>(new AstBlock());

    if(token->type == Code_Token_Type::LBRACE) 
    { 
        token_has_parsed();
        token  = get_token_to_be_parsed(); 
        auto token_pos = cur_parsed_token_pos_;

        if(is_token_eol_or_semi(token))
        {
            token_has_parsed();
        }

        auto new_statement_node = parse_statement(); 
        
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
                auto new_other_statement_node = parse_statement(); 

                if(new_other_statement_node == nullptr)
                {
                    cur_parsed_token_pos_ = token_pos;
                    break;
                }
                else 
                    new_block_node->add_statement(new_other_statement_node); 
            } 
            else 
                LOG(token->value.data(),token->line_num); 
        } 
        token = get_token_to_be_parsed();

        if(token->type == Code_Token_Type::RBRACE)
        {
            return new_block_node;
        } 
        else 
            LOG(token->value.data(),token->line_num); 
    }
    else 
        LOG(token->value.data(),token->line_num); 

    return new_block_node;
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


AstStatement::Ptr Parser::parse_statement()
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

    std::cout << "Enter in Parse statement"<< std::endl;

    //decide whether token is in the first set
    //if not 
    //Log and exit
    if(!is_in_first_set(statement_first_set_,token->type)) 
    {
        LOG(token->value.data(),token->line_num);
    }

    if(token->type == Code_Token_Type::If)
    { 
        new_if_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token));
        new_expr_node = parse_expr(); 
        
        if(new_expr_node == nullptr)
            LOG(token->value.data(),token->line_num);
        else 
        {
            new_block_node = parse_block();

            if(new_block_node == nullptr)
            {
                LOG(token->value.data(),token->line_num);
            }
            else
            {
                 token = get_token_to_be_parsed();
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
    //while clause
    else if(current_token_->type == Code_Token_Type::While)  
    {
        token_has_parsed();

        auto token  = get_token_to_be_parsed();
        if((new_expr_node = parse_expr()) != nullptr && (new_block_node = parse_block())!= nullptr)
        {
            auto new_while_node = std::shared_ptr<AstLeafNode>(new AstLeafNode(token)); 
            new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_while_node,new_expr_node,new_block_node)); 
        }
        else 
            LOG(token->value.data(),token->line_num); 
    }
    else 
    { 
        new_simple_node = parse_simple(); 

        if(new_simple_node == nullptr)
        {
            LOG(token->value.data(),token->line_num);
        }
        else 
        { 
            new_statement_node = std::shared_ptr<AstStatement>(new AstStatement(new_simple_node)); 
        }
    } 
    return new_statement_node;
}

AstProgram::Ptr Parser::parse_program()
{
    //restore current token
    auto token = get_token_to_be_parsed();
    auto cur_parsed_token_pos = cur_parsed_token_pos_;
    
    if(!is_in_first_set(program_first_set_,token->type)) 
    {
        LOG(token->value.data(),token->line_num);
    }
   


    AstProgram* new_ast_program_node = new AstProgram();

    auto new_ast_statement_node = parse_statement(); 
    
    //there is a new statement    
    if(new_ast_statement_node != nullptr)
    { 
        new_ast_program_node->add_statement(new_ast_statement_node);

        auto next_token = get_token_to_be_parsed();

        if(is_token_eol_or_semi(next_token)) 
        {
            token_has_parsed();
        }
        else 
            LOG(next_token->value.data(),next_token->line_num); 
    }
    else 
    {
        //
        set_token_parsed_pos(cur_parsed_token_pos);

        if(is_token_eol_or_semi(token))
        {
            token_has_parsed();
            new_ast_program_node = nullptr;
        }
        else 
            LOG(token->value.data(),token->line_num); 
    } 
    return std::shared_ptr<AstProgram>(new_ast_program_node); 
}

void Parser::parse()
{ 
          
    AstProgram::Ptr ptr = nullptr;

    while(cur_parsed_token_pos_< total_token_num_)
    { 
        ptr = parse_program(); 
        program_.push_back(ptr); 
        auto token = get_token_to_be_parsed(); 
        std::cout << "the next line " << token->value.data()<< std::endl;
    }

    if(cur_parsed_token_pos_ == total_token_num_)
    {
        err_state_ = 0;
        std::cout << "Success" << std::endl;
    }

}

Parser::~Parser()
{

}
