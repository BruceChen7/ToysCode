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


    class AstLeafNode 
    { 
        public:
            class IVisitor
            {
                public:
                    virtual void visit(AstNumber* number) = 0;
                    virtual void visit(AstIdentifier* identifer) = 0;
                    virtual void visit(AstOperation* operation) = 0;
                    virtual void visit(AstString* operation) = 0; 
            }; 
            virtual void accept(IVisitor *interface) = 0; 
    };

   
    class AstNumber:public AstLeafNode
    { 

        public:
            void accept(IVisitor* visitor)
            { 
                visitor->visit(this);
                
            }
        private:
            std::shared_ptr<struct Token> token;

    
    };


}
#endif
