#include "re_to_nfa.hpp"
#include <iostream>

int NFA::get_final_status()
{
	return final_status_;
}

int NFA::get_status_num()
{
	return status_.size(); 
}

void NFA::set_final_status(int status)
{
	final_status_ = status;
}

void NFA::set_transition(int begin_status,int end_status,char trans_symbol)
{
	transition new_trans;
	new_trans.begin_status = begin_status;
	new_trans.end_status = end_status;
	new_trans.trans_symbol = trans_symbol; 
	transition_list_.push_back(new_trans); 

}

void NFA::display_nfa()
{
	auto it = transition_list_.cbegin();

	for(;it != transition_list_.cend();it++)
	{
		std::cout << it->begin_status << "---->" << it->end_status<<" :Symbol -" << it->trans_symbol << endl;
	
	} 

}

void NFA::set_status(int status)
{
	for(auto i = 0 ; i < status; i++)
		status_.push_back(i); 
}


NFA concatenate_nfa(NFA first,NFA second)
{
	transition concatenated_trans; 
	NFA concatenated_nfa; 

	//after concatenation
	//the status num is the first NFA's status num + sencond NFA's status num;
	//the status num begins from 0
	concatenated_nfa.set_status(first.get_status_num()+second.get_status_num());
	


	
}


