#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include <stdio.h>
#include <stdlib.h>
struct node {
    struct node* left;
    struct node* right;
    int value; 
};

struct node *creat_new_node(int data);
struct node *bst_insert(struct node *root , int data);
void print_in_order(struct node *root); 

// Given A binary Tree, how do you remove all the half nodes (which has only one child)? 
// Note leaves should not be touched as they have both children as NULL.
//        2
//      /   \
//     7    5
//    / \  / \
//      6     9
//     / \   / \
//    1  11 4 
// after removing 
//
//     2
//    / \
//   6   4
//  / \
// 1  11
struct node* remove_half_leaf(struct node* root);

// get the binary tree's depth
int  get_binary_tree_depth(struct node* root);
//return the kth kth_largetst_node_for
struct node*  kth_largetst_node_for_bst(struct node *root, int k);

void kth_largetst_node_for_bst_uitl(struct node *root,int k, int *cnt,struct node **kth_node); 

//swap the left and right tree
void swap_left_right_child_tree(struct node* root);

#endif

