#ifndef __STONE_SRC_STONE_AST__
#define __STONE_SRC_STONE_AST__
#include <memory>
namespace Stone
{
	namespace Ast
	{
		class AstNode;
		class AstStatement;
		class AstExpr;

		class AstVisitor;
		class AstStatementVistor;
		class AstExprVistor;


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

	}


}
#endif
