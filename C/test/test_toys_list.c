#include "../src/toys_list.h"
#include <check.h>		
#include <string.h> 
#include <stdio.h>

START_TEST(test_toys_list_create)
{

	toys_list *list = toys_list_create();
	ck_assert_ptr_eq(list->head,NULL);
	ck_assert_ptr_eq(list->tail,NULL);
	ck_assert_ptr_eq(list->free,NULL);
	ck_assert_ptr_eq(list->dup,NULL);
	ck_assert_ptr_eq(list->len, 0); 
}
END_TEST 

START_TEST(test_toys_list_add_node_head)
{
	int value = 4;
	toys_list *list = toys_list_create();
	toys_list_add_node_head(list,&value);

	ck_assert_int_eq(list->len,1);
	ck_assert_int_eq(*(int *)(list->head->value),4);
	
}
END_TEST

Suite* sds_suit(void) 
{

	Suite *s = suite_create("Toy List Basic Api Testing ");
	TCase* tc_core = tcase_create("core case");
	tcase_add_test(tc_core,test_toys_list_create); 
	tcase_add_test(tc_core,test_toys_list_add_node_head);
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
