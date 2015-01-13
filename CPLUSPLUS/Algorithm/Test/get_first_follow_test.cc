#include "../../STL.h"
#include "../get_first_follow.cc"

using namespace Toyscode ;
using namespace Algorithm;

void separate_test(std::string test_name)
{
	std::cout <<"===============" << test_name << "======================" << std::endl;

}

TEST_CASE("GET first or follow set", "[Follow and first set]")
{
	separate_test("===================================");
	separate_test("Test for Get first and follow set ");
	Expr::ExprVec expr_list;

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
	
	/* /1* //T==>FM *1/ */
	Expr new_expr3("T","FM");
	expr_list.push_back(new_expr3);
	
	//M==>*FM
	Expr new_expr4("M","*FM"); 
	expr_list.push_back(new_expr4);

	//M==>""
	Expr new_expr5("M","");
	expr_list.push_back(new_expr5);

	//F==>(E)
	Expr new_expr6("F","(E)");
	expr_list.push_back(new_expr6);

	//F==>-
	Expr new_expr7("F","-");
	expr_list.push_back(new_expr7); 

	//T==>-
	Expr new_expr8("T","");
	expr_list.push_back(new_expr8);

	Expr new_expr9("T","YT");
	expr_list.push_back(new_expr9);

	//expression's number is 8
	REQUIRE(expr_list.size() == 10);

	//init production_list
	Productions production_list(expr_list);

	separate_test("show productions");
	//show the expressions
	production_list.print_production();

	Productions::StringVec terminal;
	terminal.push_back("+");
	terminal.push_back("");
	terminal.push_back("(");
	terminal.push_back(")");
	terminal.push_back("*");
	terminal.push_back("-"); 

	separate_test("show terminal symbols");
	production_list.set_terminal_symbol(terminal);
	production_list.show_terminal_symbol();

	separate_test("show nullable set ");
	production_list.get_nullable_set();
	production_list.show_nullable_set();

	separate_test("show non terminal symbol:");
	production_list.show_non_terminal_symbol();
	
	REQUIRE(production_list.is_in_null_sets("T") == true);
	REQUIRE(production_list.is_in_null_sets("Y") == true);

	separate_test("get first set  of these productions");
	production_list.get_first_set();
	production_list.show_first_set();
}
