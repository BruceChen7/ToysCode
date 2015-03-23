#include "../toys_list.h"
#include <criterion/criterion.h>
#include <string.h> 
#include <stdio.h>

Test(test_toys_list_create,create)
{

	toys_list *list = toys_list_create();
	assert_eq(list->head,NULL);
	assert_eq(list->tail,NULL);
	assert_eq(list->free,NULL);
	assert_eq(list->dup,NULL);
	assert_eq(list->len, 0); 
}

Test(test_toys_list_add_node_head,add_node_head)
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


	assert_eq(list->len,4);
	assert_eq(*(int *)(list->head->value),7);
	assert_eq(*(int *)(list->head->next->value),5);
	assert_eq(*(int *)(list->head->next->next->value),4);
    assert_eq(*(int *)(list->tail->value),8);

	toys_list_node *node = toys_list_index(list,0); 
	assert_eq(*(int *)(node->value),7); 

	node = toys_list_index(list,1);
	assert_eq(*(int *)(node->value),5); 
	
	node = toys_list_index(list,2);
	assert_eq(*(int *)(node->value),4); 

	node = toys_list_index(list, -1);
	assert_eq(*(int *)(node->value),8); 

	node = toys_list_index(list, -2);
	assert_eq(*(int *)(node->value),4); 

	node = toys_list_index(list,-3);
	assert_eq(*(int *)(node->value),5); 

	node = toys_list_search_key(list,&value2);
	assert_eq(*(int *)node->value,5); 


}


