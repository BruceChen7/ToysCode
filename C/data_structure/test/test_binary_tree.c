#include "../binary_tree.h"
#include <check.h>
START_TEST(test_binary_tree)
{
    struct node *new_node =  creat_new_node(2);
    new_node->left = creat_new_node(7);
    new_node->right = creat_new_node(5);
    new_node->left->right = creat_new_node(6);
    new_node->left->right->left =  creat_new_node(1); 
    new_node->left->right->right = creat_new_node(11);
    new_node->right->right = creat_new_node(9);
    new_node->right->right->left = creat_new_node(4);
    
    fprintf(stdout,"Inorder traversal of given tree \n");

    print_in_order(new_node);
    printf("\n");
    fprintf(stdout,"After removing Half nodes \n");
    struct node *new_root = remove_half_leaf(new_node);
    print_in_order(new_root);
    ck_assert_int_eq(new_root->value,2);
    ck_assert_int_eq(new_root->left->value,6);


}
END_TEST 


Suite* sds_suit(void) 
{

	Suite *s = suite_create(" binary tree testing ");
	TCase* tc_core = tcase_create("core case");
	tcase_add_test(tc_core,test_binary_tree); 
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
