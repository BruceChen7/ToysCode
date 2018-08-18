#ifndef __BINARY_TREE__
#define __BINARY_TREE__

#include <stdio.h>
#include <stdlib.h>
struct Node {
  struct Node *left;
  struct Node *right;
  int value;
};

struct Node *creat_new_node(int data);
struct Node *bst_insert(struct Node *root, int data);
void print_in_order(struct Node *root);
void print_post_order(struct Node *root);

// Given A binary Tree, how do you remove all the half nodes (which has only one
// child)? Note leaves should not be touched as they have both children as NULL.
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
struct Node *remove_half_leaf(struct Node *root);

// get the binary tree's depth
int get_binary_tree_depth(struct Node *root);
// return the kth kth_largetst_node_for
struct Node *kth_largetst_node_for_bst(struct Node *root, int k);

void kth_largetst_node_for_bst_uitl(struct Node *root, int k, int *cnt,
                                    struct Node **kth_node);

// swap the left and right tree
void swap_left_right_child_tree(struct Node *root);

#endif
