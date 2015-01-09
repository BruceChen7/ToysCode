#ifndef __CPLUSPLUS__ALGORITHM__GET_FIRST_FOLLOW_H_
#define __CPLUSPLUS__ALGORITHM__GET_FIRST_FOLLOW_H_

#include "../STL.h"

namespace Toyscode 
{
	namespace Algorithm
	{
		class Expr 
		{

			public:
				using Pstring = std::shared_ptr<std::string>;
				using ExprList = std::vector<Expr>;

				Expr(std::string left_production,std::string right_production):left_production_(left_production),
																			p_right_production_(std::make_shared<std::string>(right_production))
				{
				
				}

				Expr(const  Expr &rhs)
				{
					left_production_ = rhs.get_left_production();
					p_right_production_ = std::make_shared<std::string>(rhs.get_right_production());

				}

				std::string get_left_production() const
				{
					return left_production_;
				}

				std::string get_right_production() const
				{
					return *p_right_production_;
				}
				
		
			private:
					std::string left_production_;
					Pstring p_right_production_; 
		
		
		};

		class Productions 
		{

			public:
				using StringList = std::vector<std::string>;
				using StringMap = std::multimap<std::string,std::string>;

				Productions(Expr::ExprList &expressions):expressions_(expressions)
														,num_of_expression_(expressions_.size())
				{
					//init the nullable_set_;
					//which can be derived as epsilon
					for(const auto &elem : expressions_)
					{
						// can be derived as epsilon
						if(elem.get_right_production() == "")
						{
							nullable_set_.push_back(elem.get_left_production());
						}
						
						auto left_symbol = elem.get_left_production();

						auto begin = non_terminal_.cbegin();
						auto end = non_terminal_.cend();

						if(find(begin,end,left_symbol)!= end)
						{
							non_terminal_.push_back(left_symbol);
						
						}

					
					}
				
				}

				int get_expr_num()
				{
					return num_of_expression_;	
				}
			
				// print all the productions	
				void print_production() const;

				// add terminals 
				void set_terminal_symbol(Productions::StringList& terminals); 

				//show all the terminal symbol
				void show_terminal_symbol()const ;
				void show_non_terminal_symbol()const;
				void show_nullable_set()const;
				void get_nullable_set();
				void get_first_set();
				void show_first_set()const;

				bool is_a_terminal(const std::string& sym);
				bool is_in_null_sets(const std::string& sym);


			private:
				Expr::ExprList expressions_;
				int num_of_expression_;
				StringList terminal_;
				StringMap  first_set_;
				StringMap follow_set_;
				StringList nullable_set_; 
				StringList non_terminal_;
				bool determin_symbol_null(const std::string& left_symbol,int pos,bool is_left);
		
		};

		

	}

}

#endif
