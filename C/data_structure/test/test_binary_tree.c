#include <criterion/criterion.h>
#include "../binary_tree.h"


Test(BinaryTree,remove_leaf)
{
    //        2
    //      /   \
    //     7    5
    //    / \  / \
    //      6     9
    //     / \   / \
    //    1  11 4 
    struct node *new_node =  creat_new_node(2);
    new_node->left = creat_new_node(7);
    new_node->right = creat_new_node(5);
    new_node->left->right = creat_new_node(6);
    new_node->left->right->left =  creat_new_node(1); 
    new_node->left->right->right = creat_new_node(11);
    new_node->right->right = creat_new_node(9);
    new_node->right->right->left = creat_new_node(4);
    
    /* fprintf(stdout,"Inorder traversal of given tree \n"); */

    /* print_in_order(new_node); */
    /* printf("\n"); */
    /* fprintf(stdout,"After removing Half nodes \n"); */

    struct node *new_root = remove_half_leaf(new_node);
    /* print_in_order(new_root); */
    assert_eq(new_root->value,2);
    assert_eq(new_root->left->value,6);
}

Test(BinarySearchTree,create_bst_tree)
{
    struct node* root = NULL;
    //           50
    //          /   \
    //          30   70
    //         / \   / \
    //         20 40 60 80
    //         
    root = bst_insert(root,50);
    bst_insert(root,30);
    bst_insert(root,20);
    bst_insert(root,40);
    bst_insert(root,70);
    bst_insert(root,60);
    bst_insert(root,80);

    assert_eq(root->value,50);
    assert_eq(root->left->value,30);
    assert_eq(root->right->value,70);
    assert_eq(root->left->left->value,20);
    assert_eq(root->left->right->value,40);
    assert_eq(root->right->left->value,60);
    assert_eq(root->right->right->value,80);


}

Test(BinaryTree,get_binary_tree_depth)
{

    struct node *new_node =  creat_new_node(2);
    new_node->left = creat_new_node(7);
    new_node->right = creat_new_node(5);
    new_node->left->right = creat_new_node(6);
    new_node->left->right->left =  creat_new_node(1); 
    new_node->left->right->right = creat_new_node(11);
    new_node->right->right = creat_new_node(9);
    new_node->right->right->left = creat_new_node(4);
    new_node->right->right->left->right= creat_new_node(4);
    assert_eq(get_binary_tree_depth(new_node),5); 
}

Test(BinarySearchTree,kth_largest_node)
{
    struct node* root = NULL;
    root = bst_insert(root,50);
    bst_insert(root,30);
    bst_insert(root,20);
    bst_insert(root,40);
    bst_insert(root,70);
    bst_insert(root,60);
    bst_insert(root,80); 

    struct node* kth_node = kth_largetst_node_for_bst(root,4);
    assert_eq(kth_node->value,50);

    kth_node = kth_largetst_node_for_bst(root,1);
    assert_eq(kth_node->value,80);
    kth_node = kth_largetst_node_for_bst(root,2);
    assert_eq(kth_node->value,70);
}
