#include "get_first_follow.h"
#include <utility> // used for make_pair
using namespace Toyscode;
using namespace Algorithm;
#include <map> // used for multimap

using std::endl;
using std::string;
using std::cout;

bool Productions::is_a_terminal(const string& sym) 
{
	auto begin = terminal_.cbegin();
	auto end = terminal_.cend();

	if(find(begin,end,sym) != end )
	{
		return true;
	}
	else 
		return false;

}

bool Productions::is_in_null_sets(const string &symbol)
{
	auto begin = nullable_set_.cbegin();
	auto end = nullable_set_.cend();

	if(find(begin,end,symbol) != end)
	{
		return true;
	}
	else 
		return false;


}


void Productions::show_non_terminal_symbol() const
{
	for(const auto &elem : non_terminal_)
	{
		cout << elem <<endl;
	}

}
//
/* void Productions::determin_symbo_null(const  std::string& left_symbol,int pos) */ 
/* { */ 	
/* 	if(is_in_null_sets(left_symbol)) */
/* 		return ; */
/* 	if(is_a_terminal(left_symbol)) */
/* 		return ; */
/* 	else */ 
/* 	{ */
/* 		for(auto i = 0 ; i < expressions_.size(); i++) */
/* 		{ */
/* 			auto get_left_symbol = expressions_[i].get_left_production; */

/* 			if(get_left_symbol == left_symbol */
/* 			{ */
				
/* 			} */
		
/* 		} */
			


			

/* 	} */


/* } */


//incomplete
std::string get_first_set_helper(Expr::ExprList expressions)
{

	for(auto& elem : expressions)
	{
		auto expression_right = elem.get_right_production(); 

		auto p_nonterminal = expression_right.c_str();

		for(auto i = 0 ; i < expression_right.size();i++)
		{

			//if Ti can be derived as epsilon 
			
		}
	}
	return "";

	

}

void Productions::print_production() const
{
	for(auto &iterm : expressions_)
	{
			cout << iterm.get_left_production() << "====>" 
				 << iterm.get_right_production()<< endl;
	}

	
}

void Productions::set_terminal_symbol(Productions::StringList& terminals)
{
	this->terminal_ = terminals;	

}

void Productions::show_terminal_symbol() const
{
	for(const auto& elem : terminal_)
	{
		std::cout << elem << std::endl;
	}

}

void Productions::show_nullable_set() const
{
	for(const auto& elem : nullable_set_)
	{
		std::cout << elem << std::endl;
	}

}

void Productions::get_first_set()
{
	//get terminal's first set which are themselves;
	for(const auto& elem : terminal_)
	{
		
		first_set_.insert(std::make_pair(elem,elem));
	
	}

	//there is a production which can be derived as epsilon 
	//here we use "" to stand for epsilon
	for(auto &elem : expressions_)
	{
		if(elem.get_right_production() == "")		
		{
			first_set_.insert(std::make_pair(elem.get_left_production(),elem.get_right_production()));
		}
	}

	//for production X ==> Y1Y2Y3Y4 
	get_first_set_helper(expressions_);

}

void Productions::show_first_set() const
{
	for(const auto& elem : first_set_)
	{
		std::cout << "FIRST("<< elem.first <<")" <<"===>" << elem.second << std::endl;
	}
	

}
