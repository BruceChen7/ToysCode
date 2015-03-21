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
#endif

