#include "../src/toys_sds.h"
#include <check.h>		
#include <string.h> 
#include <stdio.h>

START_TEST(test_toys_sds)
{
	sds test_string= "Hello world";

	//create the first 2 word string from the test_string 
	sds new_string =  toys_sds_new_len(test_string,2); 
	ck_assert_str_eq("He",new_string);

	//test for toys_sds_len
	size_t len = toys_sds_len(new_string);
	ck_assert_uint_eq(len,2);

	//test for toys_sds_new
	sds new_string2 = toys_sds_new(test_string);
	ck_assert_str_eq(test_string,new_string2);
	ck_assert_uint_eq(strlen(test_string),strlen(new_string2));

	//test for toys_sds_empty
	ck_assert_str_eq("",toys_sds_empty()); 
	toys_sds_free(new_string);

	//test for toys_sds_toupper 
	toys_sds_toupper(new_string2);
	ck_assert_str_eq(new_string2,"HELLO WORLD");

	//test for toys_sds_tolower
	toys_sds_tolower(new_string2);
	ck_assert_str_eq(new_string2,"hello world"); 

	//test for toys_sds_avail
	ck_assert_int_eq(toys_sds_avail(new_string2),0);

}
END_TEST




Suite* sds_suit(void)
{

	Suite *s = suite_create("Toy SDS Basic Api Testing ");
	TCase* tc_core = tcase_create("core case");
	tcase_add_test(tc_core,test_toys_sds); 
	suite_add_tcase(s,tc_core);
	return s; 
}

int main()
{
	int number_failed ;
	// the new suit to be test
	Suite* s =  sds_suit(); 
	SRunner*  sr = srunner_create(s);

	srunner_run_all(sr,CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return 0; 
}
