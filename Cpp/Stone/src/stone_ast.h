#ifndef __STONE_SRC_STONE_AST__
#define __STONE_SRC_STONE_AST__
#include <memory>
#include <vector>
#include "lexical.h"

namespace Stone
{
    class AstLeafNode;
    class AstNumber;
    class AstIdentifier;
    class AstString;
    class AstOperation;


    class IVisitor
    {
        public:
            virtual bool visit(AstNumber* number) = 0;
            virtual bool visit(AstIdentifier* identifer) = 0;
            virtual bool visit(AstOperation* operation) = 0;
            virtual bool visit(AstString* operation) = 0; 
    }; 
    
    /**
     * It's a base class used by AstNumber, AstIdentifier
     * AstString class
     *
     */
    class AstLeafNode 
    { 
        public:
            virtual bool parse(IVisitor* visitor) = 0; 

            std::shared_ptr<struct Token> get_token()
            { 
                return token_;
            }
        private:
            std::shared_ptr<struct Token> token_; 
    };

    
   
    class AstParser:public IVisitor
    { 
        public:
            bool visit(AstNumber* number);
            bool visit(AstString* string);
            bool visit(AstIdentifier* Identifier); 
            bool visit(AstOperation* opeation);

        private: 
            //private method 
            bool parse_ast_leaf(AstLeafNode* node, Code_Token_Type type);

            //data member
            int err_line_num_; 
            std::string err_msg_;
    }; 



    class AstNumber:public AstLeafNode
    { 

        public:
            using Ptr = std::shared_ptr<struct Token>;

            bool parse(IVisitor* visitor)
            { 
                return visitor->visit(this); 
                
            } 

    }; 

    class AstString:public AstLeafNode
    {
        public:
            using Ptr = std::shared_ptr<struct Token>;

            bool parse(IVisitor* visitor)
            {
                return visitor->visit(this);
            }
    };

    class AstIdentifier:public AstLeafNode
    { 
        public:
            using Ptr = std::shared_ptr<struct Token>;

            bool parse(IVisitor* visitor)
            {
                return visitor->visit(this);
            }

    };


}
#endif
