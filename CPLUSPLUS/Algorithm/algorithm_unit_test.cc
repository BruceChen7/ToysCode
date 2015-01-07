#include "re_to_nfa.cc"
#include "../STL.h"
#include "get_first_follow.h"
#include <memory>


using namespace Toyscode;
using namespace Algorithm;

void separate_test(std::string test_name)
{
	std::cout <<"===============" << test_name << "======================" << std::endl;

}


TEST_CASE("Init NFA","Init NFA class ")
{

	separate_test("Init NFA");
	NFA test;
	NFA test1;
	test.set_status(2);
	test.set_transition(0,1,'a');
	test.set_final_status(1);
	//
	REQUIRE(test.get_final_status()==1);
	test.display_nfa();
	
}

TEST_CASE("GET first or follow set", "[Follow and first set]")
{
	separate_test("Test for Get first and follow set ");
	Expr::ExprList expr_list;

	//E==> TY
	Expr new_expr("E","TY");
	expr_list.push_back(new_expr);

	REQUIRE(new_expr.get_left_production() =="E");
	REQUIRE(new_expr.get_right_production() == "TY");


	//Y==>+TY
	Expr new_expr1("Y","+TY");
	expr_list.push_back(new_expr1);

	//Y==>"" means is a null string
	Expr new_expr2("Y","");
	expr_list.push_back(new_expr2);
	
	//T==>FM
	Expr new_expr3("T","FM");
	expr_list.push_back(new_expr3);
	
	//M==>*FM
	Expr new_expr4("M","*FM"); 
	expr_list.push_back(new_expr4);

	//M==>""
	Expr new_expr5("M","");
	expr_list.push_back(new_expr5);

	Expr new_expr6("F","(E)");
	expr_list.push_back(new_expr6);

	//F==>-
	Expr new_expr7("F","-");
	expr_list.push_back(new_expr7); 



	REQUIRE(expr_list.size() == 8);
	
	Productions production_list(expr_list);
	production_list.print_production();

}




