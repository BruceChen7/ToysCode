#include <Utilities/include/re_to_nfa.h>
#include <iostream>

using  namespace Toyscode;
using namespace Utilities;

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

// add a transition to the NFA 
void NFA::set_transition(int begin_status,int end_status,char trans_symbol)
{
    transition new_trans;
    new_trans.begin_status = begin_status;
    new_trans.end_status = end_status;
    new_trans.trans_symbol = trans_symbol; 
    transition_list_.push_back(new_trans); 

}

void NFA::copy_transtion_list(std::vector<transition>& transition_list)
{
    auto it = transition_list_.cbegin();
    transition new_transition;

    for(; it != transition_list_.cend();it++)
    {
        new_transition.begin_status = it->begin_status;
        new_transition.end_status = it->end_status;
        new_transition.trans_symbol = it->trans_symbol;
        transition_list.push_back(new_transition); 
    }
    

}



void NFA::display_nfa()
{
    auto it = transition_list_.cbegin(); 
    for(;it != transition_list_.cend();it++)
    {
        std::cout << it->begin_status << "---->" << it->end_status<<" :  Symbol : " << it->trans_symbol << std::endl;
    
    } 


}

void NFA::set_status(int status)
{
    for(int i = 0 ; i < status; i++)
        status_.push_back(i); 
}


NFA concatenate_nfa(NFA first,NFA second)
{
    std::vector<transition> concatenated_trans; 
    NFA concatenated_nfa; 

    //after concatenation
    //the status num is the first NFA's status num + sencond NFA's status num;
    //the status num begins from 0
    concatenated_nfa.set_status(first.get_status_num()+second.get_status_num()); 

    //now the transition of first NFA is in concatenated_trans
    first.copy_transtion_list(concatenated_trans);
    
    auto it = concatenated_trans.cbegin();

    for(;it != concatenated_trans.cend();it++)
    {
        concatenated_nfa.set_transition(it->begin_status,it->end_status,it->trans_symbol);
    }
    
    //clear all the first NFA's transition
    concatenated_trans.clear();

    //now the transition of first NFA is in concatenated_trans
    second.copy_transtion_list(concatenated_trans);

    it = concatenated_trans.cbegin();
    
    for(;it != concatenated_trans.cend();it++)
    {
        concatenated_nfa.set_transition(it->begin_status+first.get_status_num(),it->end_status+first.get_status_num(),it->trans_symbol);
    }

    //set the last status is the final status
    concatenated_nfa.set_final_status(first.get_status_num() + second.get_status_num()); 
    
    return concatenated_nfa; 
} 


