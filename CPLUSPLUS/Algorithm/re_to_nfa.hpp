#include <string>
#include <stack>
#include <vector>

struct transition {
	int begin_status;
	int end_status;
	char trans_symbol; 

};

class NFA {
	public:
		NFA();

		//get accepted status;
		int get_final_status(); 
		// set accepted status;
		void set_final_status(int status);
		
		void set_status(int status);
		void set_transition(int begin_status,int end_status,char trans_symbol);
		int get_status_num();

		//
		int get_transition_list(transition &);

		void display_nfa(); 

	private:
		std::vector<int> status_;
		int final_status_; 
		std::vector<transition> transition_list_; 

};

