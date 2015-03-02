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
	//7->5->4->8
	int value1 = 4;
	toys_list *list = toys_list_create();
	toys_list_add_node_head(list,&value1);

	int value2 = 5;
	toys_list_add_node_head(list,&value2);

	int value3 = 7;
	toys_list_add_node_head(list,&value3);
	
	int value4 = 8;
	toys_list_add_node_tail(list,&value4);


	ck_assert_int_eq(list->len,4);
	ck_assert_int_eq(*(int *)(list->head->value),7);
	ck_assert_int_eq(*(int *)(list->head->next->value),5);
	ck_assert_int_eq(*(int *)(list->head->next->next->value),4);
	ck_assert_int_eq(*(int *)(list->tail->value),8);

	toys_list_node *node = toys_list_index(list,0); 
	ck_assert_int_eq(*(int *)(node->value),7); 

	node = toys_list_index(list,1);
	ck_assert_int_eq(*(int *)(node->value),5); 
	
	node = toys_list_index(list,2);
	ck_assert_int_eq(*(int *)(node->value),4); 

	node = toys_list_index(list, -1);
	ck_assert_int_eq(*(int *)(node->value),8); 

	node = toys_list_index(list, -2);
	ck_assert_int_eq(*(int *)(node->value),4); 

	node = toys_list_index(list,-3);
	ck_assert_int_eq(*(int *)(node->value),5); 

	node = toys_list_search_key(list,&value2);
	ck_assert_int_eq(*(int *)node->value,5);
		
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
