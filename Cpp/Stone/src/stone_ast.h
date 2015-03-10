#ifndef __STONE_SRC_STONE_AST__
#define __STONE_SRC_STONE_AST__
#include <memory>
#include <vector>
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
				virtual ~AstNode() = 0;
				virtual void accept(AstVisitor *visitor) = 0;
		
		};
		
		class AstWithChildNode: public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstWithChildNode>;
				virtual void accept(AstVisitor *visitor) = 0;
		
		};

		class AstLeafNode:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstLeafNode> ;
				virtual void accept(AstVisitor *visitor)  = 0;
		};

		class AstStatement:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstStatement> ;
				void accept(AstVisitor* visitor)  override;
			private:
				std::vector<AstNode::Ptr> child_;
		};

		class AstExpr:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstExpr>;
				void accept(AstVisitor *visitor) override;
			private:
				std::vector<AstNode::Ptr> child_;
		};

		class AstPrimary:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstPrimary>;
				void accept(AstVisitor *visitor) override ;
		};
		
		class AstFactor:public AstWithChildNode 
		{
			public:
				using Ptr = std::shared_ptr<AstFactor>;
				using WeakPtr = std::shared_ptr<AstFactor>;
				void accept(AstVisitor * vistor)  override;
		};

		class AstNumber:public AstLeafNode
		{
			public:
				using Ptr = std::shared_ptr<AstNumber>;
				using WeakPtr = std::weak_ptr<AstNumber>;
				void accept(AstVisitor *visitor)  override;
		
		};

		class AstIdentifier:public AstLeafNode
		{
			public:
				using Ptr= std::shared_ptr<AstIdentifier>;
				using WeakPtr = std::weak_ptr<AstIdentifier>;
				void accept(AstVisitor *visitor)  override;
		
		};
		class AstString:public AstNode 
		{
			public:
				using Ptr = std::shared_ptr<AstString>;
				using WeakPtr = std::shared_ptr<AstString>;
				void accept(AstVisitor * vistor)  override;
		
		};

		class AstBlock:public AstWithChildNode
		{ 
			public:
				using Ptr = std::shared_ptr<AstBlock>;
				using WeakPtr = std::weak_ptr<AstBlock>;
				void accept(AstVisitor* visitor)  override;
		};
		class AstOperation:public AstLeafNode
		{
			public:
				using Ptr = std::shared_ptr<AstOperation>;
				using WeakPtr = std::weak_ptr<AstOperation>;
				void accept(AstVisitor* visitor)  override;
		};

		class AstSimple:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstSimple>;
				using WeakPtr = std::weak_ptr<AstSimple>;
				void accept(AstVisitor* visitor) override;

		};

		class AstProgram:public AstWithChildNode
		{
			public:
				using Ptr = std::shared_ptr<AstProgram>;
				using WeakPtr = std::weak_ptr<AstProgram>;
				void accept(AstVisitor* visitor)  override;
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
		class AstPrimary : public AstVisitor
		{
			public:
				virtual void visit(AstWithChildNode *node)
		}
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
