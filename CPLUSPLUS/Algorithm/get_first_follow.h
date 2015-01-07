#ifndef __CPLUSPLUS__ALGORITHM__GET_FIRST_FOLLOW_H_
#define __CPLUSPLUS__ALGORITHM__GET_FIRST_FOLLOW_H_

#include "../STL.h"

namespace Toyscode 
{
	namespace Algorithm
	{
		class Expr {

			public:
				using Pstring = std::shared_ptr<std::string>;
				using ExprList = std::vector<Expr>;

				Expr(std::string left_production,std::string right_production):left_production_(left_production),
																			p_right_production_(std::make_shared<std::string>(right_production))
				{
				
				}
			
				std::string get_left_production()
				{
					return left_production_;
				}

				std::string get_right_production()
				{
					return *p_right_production_;
				}
				
		
			private:
					std::string left_production_;
					Toyscode::Algorithm::Expr::Pstring p_right_production_; 
		
		
		};

		class Productions {

			public:
				Productions(Expr::ExprList &expressions):expressions_(expressions)
																			   ,num_of_expression_(expressions_.size())
				{
				
				}

				int get_expr_num()
				{
					return num_of_expression_;	
				}
				
				void print_production()
				{
					for(auto &iterm : expressions_)
					{
						std::cout << iterm.get_left_production() << "====>" << iterm.get_right_production()<< std::endl;
					}

					
				}




		

			private:
				Expr::ExprList expressions_;
				int num_of_expression_;
		
		
		};

		

	}

}

#endif
