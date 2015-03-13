#ifndef __STONE_SRC_STONE_AST__
#define __STONE_SRC_STONE_AST__
#include <memory>
#include <vector>
#include "lexical.h"
namespace Stone
{
	namespace Ast
	{
		//forward declaration
		class AstWithChildNode;
		class AstNode;
		class AstStatement;
		class AstExpr;
		class AstPrimary;
		class AstFactor;
		class AstNumber;
		class AstIdentifier;
		class AstString;
		class AstOperation;
		class AstBlock;
		class AstSimple;
		class AstProgram;


		class AstVisitor;
		class AstStatementVistor;
		class AstExprVistor;
		class AstFactorVisitor;
		class AstPrimaryVisitor;
		class AstNumberVisitor;
		class AstIdentifierVisitor;
		class AstStringVisitor;
		class AstOperationVistor;
		class AstBlockVisitor;
		class AstSimpleVisitor;
		class AstProgramVisitor;


		class AstNode
		{	
			public:
				using Ptr = std::shared_ptr<AstNode>; 
			 	// ~AstNode();
				void accept(AstVisitor *visitor) ;
		};
		
		class AstWithChildNode: public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstWithChildNode>;
				void accept(AstVisitor *visitor);
		
		};

		class AstLeafNode:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstLeafNode> ;
			    void accept(AstVisitor *visitor)  ;
				AstLeafNode(struct Token* token);
			private:
				std::string value_;
				int line_num_; 
				Code_Token_Type type_; 

		};

		class AstNumber:public AstLeafNode
		{
			public:
				AstNumber(struct Token* token);
				using Ptr = std::shared_ptr<AstNumber>;
				using WeakPtr = std::weak_ptr<AstNumber>;
				void accept(AstVisitor *visitor) ;
		
		};

		class AstOperation:public AstLeafNode
		{
			public:
				using Ptr = std::shared_ptr<AstOperation>;
				AstOperation(struct Token *token);
				void accept(AstVisitor* visitor)  ;
			private:
				std::string operator_;

			
		};

		class AstStatement:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstStatement> ;
				void accept(AstVisitor* visitor); 
			private:
				std::vector<AstNode::Ptr> child_;
		};


		
		class AstFactor:public AstWithChildNode 
		{
			public:
				using Ptr = std::shared_ptr<AstFactor>;
				void accept(AstVisitor * vistor) ;
		};


		class AstExpr:public AstWithChildNode
		{
			public:
				struct AstOpFactor 
				{
					AstOperation::Ptr op;
					AstFactor::Ptr factor;
				
				};
				using AstOPFactor = struct Ast_OP_Factor;

				using Ptr = std::shared_ptr<AstExpr>;
				AstExpr(AstFactor::Ptr node);
				void add_op_factor(AstOperation::Ptr op,AstFactor::Ptr factor);
				void accept(AstVisitor *visitor) ;
			private:
				AstFactor::Ptr factor_;
				std::vector<AstOpFactor> ast_op_factor_; 
		};

		class AstIdentifier:public AstLeafNode
		{
			public:
				using Ptr= std::shared_ptr<AstIdentifier>;
				AstIdentifier(struct Token* token);
				void accept(AstVisitor *visitor)  ;
			private:
				std::string value_;
				int line_num_; 
				Code_Token_Type type_; 
		};

		class AstString:public AstLeafNode
		{
			public:
				using Ptr = std::shared_ptr<AstString>;
				AstString(struct Token* token);
				void accept(AstVisitor * vistor)  ;
			private:
				std::string value_;
				int line_num_; 
				Code_Token_Type type_; 
		
		};

		class AstBlock:public AstWithChildNode
		{ 
			public:
				using Ptr = std::shared_ptr<AstBlock>;
				void accept(AstVisitor* visitor)  ;
		};

		class AstSimple:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstSimple>;
				void accept(AstVisitor* visitor) ;

		};

		class AstPrimary:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstPrimary>;
				void accept(AstVisitor *visitor) ;
				AstPrimary(AstLeafNode* node);
				AstPrimary(AstExpr::Ptr node);
			private:
				AstLeafNode::Ptr leaf_node_;
				AstExpr::Ptr expr_node_; 

		};

		class AstProgram:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstProgram>;
				AstProgram();
				void add_statement(AstStatement::Ptr statement);
				void accept(AstVisitor* visitor)  ;
			private:
				std::vector<AstStatement::Ptr> statement_;

		};

		//A General Vistor
		class AstVisitor
		{	
			public:
				virtual void visit(AstWithChildNode *node) = 0;
				virtual void visit(AstLeafNode *node) = 0;

		};
		
		//AstWithChildNode visitors
		
		class AstStatementVistor:public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override; 
		
		};

		class AstExprVistor : public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override;
		
		};
		class AstSimpleVisitor:public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override;
		
		};
		
		class AstFactorVisitor:public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override;
		};
		class AstPrimaryVisitor : public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override;
		};
		class AstBlockVisitor:public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override;
		
		
		};

		class AstProgramVisitor: public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node) override;
		
		};


		//AstLeafNode vistiors
		class AstStringVisitor:public AstVisitor
		{
			public:
				virtual void visit(AstLeafNode *node)  override;
		
		
		};
		class AstIdentifierVisitor:public AstVisitor
		{
			public:
				virtual void visit(AstLeafNode *node)  override;
		
		
		};

		class AstNumberVisitor:public AstVisitor
		{
			public:
				virtual void visit(AstLeafNode *node)  override;

		};

		class AstOperationVistor:public AstVisitor
		{
			public:
				virtual void visit(AstLeafNode *Node) override ;
		}; 
	} 
}
#endif
