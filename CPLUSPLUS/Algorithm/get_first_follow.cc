#include "get_first_follow.h"
#include <utility> // used for make_pair
#include <map> // used for multimap

using std::endl;
using std::string;
using std::cout;

bool is_belonged_to_a_set(const string& sym,Productions::StringList set)
{
	auto begin = set.cbegin();
	auto end = set.cend();

	if(find(begin,end,sym) != end)
		return true; 
	else 
		return false;

}
bool Productions::is_a_terminal(const string& sym) 
{
	return is_belonged_to_a_set(sym,terminal_);

}

bool Productions::is_in_null_sets(const string &symbol)
{
	return is_belonged_to_a_set(symbol,nullable_set_);
}


void Productions::show_non_terminal_symbol() const
{
	for(const auto &elem : non_terminal_)
	{
		cout << elem <<endl;
	}

}
//
bool Productions::determin_symbol_null(const  std::string& left_symbol,int pos,bool is_left) 
{ 	
	if(is_in_null_sets(left_symbol))
		return true;
	if(is_a_terminal(left_symbol))
		return false;
	else 
	{
		for(auto i = 0 ; i < expressions_.size(); i++)
		{			
			auto new_left_symbol = expressions_[i].get_left_production();

			// find  the productions 
			// whose left part of the productions is the same as left_symbol 
			// but can't be the same production
			if( new_left_symbol == left_symbol )
			{

				auto right_production  = expressions_[i].get_right_production();

				for(auto j = 0 ; j < right_production.size(); j++)
				{
					//construct a string for right_production[j]
					const char *tmp = &right_production[j];
					string right_symbol(tmp);
					
					// the same production and the right part of production hass also left_symbol
					// we can't determin whether if the left_symbol is a nullable symbol by this expression
					if(right_symbol == new_left_symbol && i == pos)
						break;
					else 
					{
						if(determin_symbol_null(right_symbol,i,false) == true)
							continue;
						else 
							return false; 
					} 

				 } //end of right_production  loop 
			  } // end of if 
		}

		// it must be left symbol 
		// can't be right productions' symbol
		// so it can be pushed into nullable_set_
		if(is_left == true)
			nullable_set_.push_back(left_symbol) ; 
		return true;

			

	}


}

void Productions::get_nullable_set()
{
	for(auto i = 0 ; i < expressions_.size(); i++)
	{	
		determin_symbol_null(expressions_[i].get_left_production(),i,true);

	}

}


//Todo
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
