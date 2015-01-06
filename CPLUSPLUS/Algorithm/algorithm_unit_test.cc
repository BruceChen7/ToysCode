#include "re_to_nfa.cc"
#include "../STL.h"

TEST_CASE("Init NFA","Init NFA class ")
{
	NFA test;
	NFA test1;
	test.set_status(2);
	test.set_transition(0,1,'a');
	test.set_final_status(1);
	//
	REQUIRE(test.get_final_status()==1);
	test.display_nfa();
	
}
