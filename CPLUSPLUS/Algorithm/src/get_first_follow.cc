#include "get_first_follow.h"

using namespace Toyscode;
using namespace Algorithm;
using std::endl;
using std::string;
using std::cout;

bool is_belonged_to_a_set(const string& sym,const Productions::StringVec& set)
{
	auto begin = set.cbegin();
	auto end = set.cend();

	if(find(begin,end,sym) != end)
		return true; 
	else 
		return false;

}

void Productions::find_begin_with_spec_symbol_expr(const string& left_symbol,std::vector<int>& location)
{
	for(auto i = 0u ; i < expressions_.size();i++)
	{
		if(expressions_[i].get_left_production() == left_symbol)
		{
			location.push_back(i); 
		}
	}
	
}

int Productions::get_left_sym_pos_in_set(const string& sym) const

{
	auto length = first_set_.size();
	unsigned int i;
	for(i  = 0u; i < length; i++)
	{
		if(first_set_[i].symbol_name == sym)
			break;
	}

	if( i == 0)
		return -1;		
	else 
		return i;

}


//从右推导式子中找到第一个属于'nullabe set'的最后符号
//返回其在右推导式的位置
int Productions::find_first_nullable_sym(const string& right_production) const
{
	auto i = -1;
	for(unsigned int j = 0 ; j < right_production.size();j++)
	{
		string temp(1,right_production[j]);
		if(is_in_null_sets(temp))
			i++;
		else 
			break; 
	}
	
	return i; 
}

//判断该符号是否是终结符
bool Productions::is_a_terminal(const string& sym) 
{
	return is_belonged_to_a_set(sym,terminal_);

}

bool Productions::is_in_null_sets(const string &symbol)const
{
	return is_belonged_to_a_set(symbol,nullable_set_);
}

bool Productions::is_belonged_to_first_set(const string& symbol, StringVec& set)
{
	return is_belonged_to_a_set(symbol,set);
}

void Productions::show_non_terminal_symbol() const
{
	for(const auto &elem : non_terminal_)
	{
		cout << elem <<endl;
	}

}
//
bool Productions::determin_symbol_null(const std::string& left_symbol,unsigned int pos,bool is_left) 
{ 	
	if(is_in_null_sets(left_symbol))
		return true;
	if(is_a_terminal(left_symbol))
		return false;
	else 
	{
		for(unsigned int  i = 0 ; i < expressions_.size(); i++)
		{			
			auto new_left_symbol = expressions_[i].get_left_production();

			// find  the productions 
			// whose left part of the productions is the same as left_symbol 
			// but can't be the same production
			if( new_left_symbol == left_symbol )
			{

				auto right_production  = expressions_[i].get_right_production();

				for(unsigned int j = 0 ; j < right_production.size(); j++)
				{
					//construct a string for right_production[j]
					string right_symbol = string(1,right_production[j]);	

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
	for(unsigned int i = 0 ; i < expressions_.size(); i++)
	{	
		determin_symbol_null(expressions_[i].get_left_production(),i,true);

	}

}

void Productions::get_first_set()
{
	if(is_first_set_filled_flag)
		return;
	std::vector<std::string> first; 
	auto i = 0;

	for(const auto &left_symbol:non_terminal_)
	{ 
		get_first_set_helper(left_symbol,first); 

		Set new_set;
		new_set.symbol_name = left_symbol;
		new_set.first_or_follow_set = first; 
		first_set_.push_back(new_set); 
		first.clear(); 
	}

	is_first_set_filled_flag = true; 
}

void Productions::show_first_set(const std::string& non_terminal)
{ 
	if(is_a_terminal(non_terminal))
		std::cout <<  non_terminal << " ====> " << non_terminal;
	else 
	{
		for(const auto&set : first_set_)
		{
			if(set.symbol_name == non_terminal)
			{
				std::cout << non_terminal << " ====> ";

				for(const auto &terminal : set.first_or_follow_set)
					std::cout << terminal << " ";

				std::cout << std::endl;
				std ::cout << "the num of first set is " << set.first_or_follow_set.size()<< std::endl;
			}
				
		}
	
	}





}

void Productions::print_production() const
{
	for(auto &iterm : expressions_)
	{
			cout << iterm.get_left_production() << "====>" 
				 << iterm.get_right_production()<< endl;
	}

	
}

void Productions::set_terminal_symbol(Productions::StringVec& terminals)
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


//找到所有的以left_production开始的文法
//找到left_production对应的follow set
//把它输出到first_set中
void Productions::get_first_set_helper(const std::string& left_production,std::vector<std::string>& first_set)
{
	std::vector<int> pos;
	find_begin_with_spec_symbol_expr(left_production,pos);
	
	for(auto &i : pos)
	{
		auto right_production =  expressions_[i].get_right_production();
		auto num = find_first_nullable_sym(right_production); 

		if(num == -1)
		{
			
			string right_symbol;

			if(right_production.length() == 0)
				right_symbol = "";
			else 
				//当right_production 为空字符串时
				//下面的等式不是为空，其长度为1
				//而空字符串的长度为0
				right_symbol = string(1,right_production[0]);

			if(right_symbol == "")
			{ 

				if(!is_belonged_to_first_set(right_production,first_set))
				{
					first_set.push_back(right_production);
				}
					
			}

			else if(is_a_terminal(right_symbol))
			{
				if(!is_belonged_to_first_set(right_symbol,first_set))
				{
					first_set.push_back(right_symbol);
				}

			}
			else if(right_symbol == left_production)
				continue;
			else 
			{
				std::vector<std::string>right_first_set;
				get_first_set_helper(right_symbol,right_first_set); 


				for(const auto &elem:right_first_set)
				{
					if(!is_belonged_to_first_set(elem,first_set))
						first_set.push_back(elem);

				}
			
			}

		} 
		else 
		{
			for(auto j = 0 ; j <= num+1 ; j++)
			{
				std::vector<std::string> right_first_set;
				string right_symbol(1,right_production[j]);

				if(right_symbol == left_production)
					break;
				get_first_set_helper(right_symbol,right_first_set);


				for(const auto &elem:right_first_set)
				{
					//避免重复的first集合
					if(!is_belonged_to_first_set(elem,first_set))
						first_set.push_back(elem);

				}
			} 
		
		}
	}


}

//将文法产生式子的follow 集合放到follow_set中
void Productions::get_follow_set_helper(const Expr& expr,Set& follow_set)
{

	auto left_symbol = expr.get_left_production();
	auto right_production = expr.get_right_production(); 



}

//获取follow set 
void Productions::get_follow_set()
{
	if(!is_first_set_filled())
		get_first_set();
	
	for(const auto &expr : expressions_)
	{
		Set follow_set;
		get_follow_set_helper(expr,follow_set);
		
	}

}



bool Productions::is_first_set_filled()
{ 
	return is_first_set_filled_flag;
}

void Productions::show_first_set() const
{
	for(const auto& elem : first_set_)
	{
		cout << "Symbol Name : " << elem.symbol_name; 

		for(const auto& first_sym : elem.first_or_follow_set)
			cout << "  ===> "<< first_sym; 
		cout << endl;
	}

}
