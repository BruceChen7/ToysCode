#ifndef __CPLUSPLUS__ALGORITHM_RE_TO_NFA_HPP__
#define __CPLUSPLUS__ALGORITHM_RE_TO_NFA_HPP__
#include <string>
#include <stack>
#include <vector>

namespace Toyscode
{
    namespace Utilities
    {
        struct transition {
            int begin_status;
            int end_status;
            char trans_symbol; 

        };

        class NFA {
            public:
                NFA(){}

                //get accepted status;
                int get_final_status(); 
                // set accepted status;
                void set_final_status(int status);
                
                //set status from 0 to status-1;
                void set_status(int status);

                //add a transition to the NFA
                void set_transition(int begin_status,int end_status,char trans_symbol);

                //get the total status number
                int get_status_num();
                
                //transition_list is in out parameter
                //copy the transition to transition_list
                void copy_transtion_list(std::vector<transition>& transition_list); 
                void display_nfa(); 

            private:
                std::vector<int> status_;
                int final_status_; 
                std::vector<transition> transition_list_; 

        };
    }

}
#endif
