#ifndef __STONE_SRC_STONE_AST__
#define __STONE_SRC_STONE_AST__
#include <memory>
namespace Stone
{
	namespace Ast
	{
		//forward declaration
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
		class AstNumberVistor;
		class AstIdentifierVisitor;
		class AstStringVisitor;
		class AstOperationVistor;
		class AstBlockVisitor;
		class AstSimpleVisitor;
		class AstProgramVisitor;


		class AstNode : public std::enable_shared_from_this<AstNode>
		{
			public:
				using Ptr = std::shared_ptr<AstNode> ;
				using WeakPtr = std::weak_ptr<AstNode>;
				WeakPtr parent;
				AstNode();
				virtual ~AstNode() = 0;
				virtual void accept(AstVisitor *vistor) = 0;
		
		};

		class AstStatement:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstStatement> ;
				using WeakPtr = std::weak_ptr<AstStatement>;

				void accept(AstVisitor* visitor) = override;
				virtual  void accept(AstStatementVistor * visitor) = 0; 
			
		};

		class AstExpr:public AstNode 
		{
			public:
				using Ptr = std::shared_ptr<AstExpr>;
				using WeakPtr = std::weak_ptr<AstExpr>;
				void accept(AstVisitor *visitor) override;
				void accept(AstExprVistor *visitor) = 0;
		};

		class AstPrimary:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AStPrimar>;
				using WeakPtr = std::weak_ptr<AstPrimar>;
				void accept(AstVisitor *visitor) override ;
				void accept(AstPrimaryVisitor* visitor) = 0;
		};
		
		class AstFactor:public AstNode 
		{
			public:
				using Ptr = std::shared_ptr<AstFactor>;
				using WeakPtr = std::shared_ptr<AstFactor>;
				void accept(AstVisitor * vistor) = override;
				void accept(AstNumberVisitor* visitor) = 0;
		};

		class AstNumber:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstNumber>;
				using WeakPtr = std::weak_ptr<AstNumber>;
				void accept(AstVisitor *visitor) = override;
				void accept(AstNumberVistor *visitor) = 0;
		
		};

		class AstIdentifier:public AstNode
		{
			public:
				using Ptr= std::shared_ptr<AstIdentifier>;
				using WeakPtr = std::weak_ptr<AstIdentifier>;
				void accept(AstVistor *visitor) = override;
				void accept(AstIdentifierVisitor* visitor) = 0;
		
		};
		class AstString:public AstNode 
		{
			public:
				using Ptr = std::shared_ptr<AstString>;
				using WeakPtr = std::shared_ptr<AstString>;
				void accept(AstVisitor * vistor) = override;
				void accept(AstStringVisitor* visitor) = 0;
		
		};

		class AstBlock:public AstNode
		{ 
			public:
				using Ptr = std::shared_ptr<AstBlock>;
				using WeakPtr = std::weak_ptr<AstBlock>;
				void accept(AstVistor* visitor) = override;
				void accept(AstNumberVisitor* visitor) = 0;
		};

		class AstSimple:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstSimple>;
				using WeakPtr = std::weak_ptr<AstSimple>;
				void accept(AstVisitor* visitor) = override;
				void accept(AstSimpleVisitor* visitor) = 0;

		}

		class AstProgram:public AstNode
		{
			public:
				using Ptr = std::shared_ptr<AstProgram>;
				using WeakPtr = std::weak_ptr<AstProgram>;
				void accept(AstVisitor* visitor) = override;
				void accept(AstProgramVisitor* visitor) = 0 ;
		}




	}


}
#endif
