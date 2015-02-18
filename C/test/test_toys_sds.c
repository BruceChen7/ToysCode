#include "../src/toys_sds.h"
#include <check.h>		
#include <string.h> 
#include <stdio.h>

START_TEST(test_toys_sds)
{
	sds test_string= "Hello world";

	//create the first 2 word string from the test_string 
	sds y =  toys_sds_new_len(test_string,2); 
	ck_assert_str_eq("He",y);

	//test for toys_sds_len
	size_t len = toys_sds_len(y);
	ck_assert_uint_eq(len,2);

	//test for toys_sds_new
	sds x = toys_sds_new(test_string);
	ck_assert_str_eq(test_string,x);
	ck_assert_uint_eq(strlen(test_string),toys_sds_len(x));

	//test for toys_sds_empty
	ck_assert_str_eq("",toys_sds_empty()); 

	//test for toys_sds_toupper 
	toys_sds_toupper(x);
	ck_assert_str_eq(x,"HELLO WORLD");

	//test for toys_sds_tolower
toys_sds_tolower(x);
	ck_assert_str_eq(x,"hello world"); 

	//test for toys_sds_avail
	ck_assert_int_eq(toys_sds_avail(x),0);

	//test for toys_sds_expand_size
	//the size of "hello world" is 11
	//then we expand the size of the new_string2 to (11+8)*2
	//now the available free space is (11+8)*2 -11,which is 27
	ck_assert_int_eq(toys_sds_len(x),11);
	x = toys_sds_expand_size(x,8);
	ck_assert_int_eq(toys_sds_avail(x),27);

	//test for toys_sds_cat
	y = toys_sds_new(" Bruce Chen");
	x = toys_sds_cat_len(x,y,toys_sds_len(y));
	ck_assert_str_eq(x,"hello world Bruce Chen"); 

	//to ensure y has enough space 
	y = toys_sds_expand_size(y,14);
	ck_assert_str_eq(y," Bruce Chen");

	//when there is enough space 
	//x is copied into y
	toys_sds_cpy(y,x);
	ck_assert_str_eq(y,x);
	
	//when there is not enough space
	//the resturned sds is the copied x
	y  = toys_sds_empty();
	y = toys_sds_cpy(y,x);
	ck_assert_str_eq(y,x);


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
