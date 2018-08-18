#include "binary_tree.h"
struct Node *creat_new_node(int data) {
  struct Node *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL) fprintf(stderr, "can't creat a new Node\n");
  new_node->value = data;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

// inorder traversal
void print_in_order(struct Node *root) {
  if (root != NULL) {
    print_in_order(root->left);
    fprintf(stdout, "%d ", root->value);

    print_in_order(root->right);
  }
}

void print_post_order(struct Node *root) {
  if (root != NULL) {
    print_post_order(root->left);
    print_post_order(root->right);
    fprintf(stdout, "%d", root->value);
  }
}
struct Node *remove_half_leaf(struct Node *root) {
  if (root == NULL) return NULL;
  root->left = remove_half_leaf(root->left);
  root->right = remove_half_leaf(root->right);

  if (root->left == NULL && root->right == NULL) return root;

  if (root->left == NULL) {
    struct Node *new_node = root->right;
    free(root);
    return new_node;
  }
  if (root->right == NULL) {
    struct Node *new_node = root->left;
    free(root);
    return new_node;
  }
  return root;
}

// binary search tree insert
struct Node *bst_insert(struct Node *root, int data) {
  if (root == NULL) {
    return creat_new_node(data);
  } else if (data < root->value) {
    root->left = bst_insert(root->left, data);
  } else {
    root->right = bst_insert(root->right, data);
  }
  return root;
}

int get_binary_tree_depth(struct Node *root) {
  int depth;
  if (root == NULL) {
    return 0;
  } else {
    int left_depth = get_binary_tree_depth(root->left) + 1;
    int right_depth = get_binary_tree_depth(root->right) + 1;

    depth = (left_depth > right_depth) ? left_depth : right_depth;
  }
  return depth;
}

void kth_largetst_node_for_bst_uitl(struct Node *root, int k, int *cnt,
                                    struct Node **kth_node) {
  if (root == NULL || *cnt >= k) {
    return;
  }

  kth_largetst_node_for_bst_uitl(root->right, k, cnt, kth_node);
  (*cnt)++;

  if (*cnt == k) {
    *kth_node = root;
    return;
  }

  kth_largetst_node_for_bst_uitl(root->left, k, cnt, kth_node);
}

// Get the kth most  largest value
struct Node *kth_largetst_node_for_bst(struct Node *root, int k) {
  int cnt = 0;
  struct Node *kth_node = NULL;

  kth_largetst_node_for_bst_uitl(root, k, &cnt, &kth_node);

  return kth_node;
}

// swap the left and right  subtree
void swap_left_right_child_tree(struct Node *node) {
  if (node == NULL) return;
  swap_left_right_child_tree(node->left);
  swap_left_right_child_tree(node->right);

  struct Node *temp = node->left;
  node->left = node->right;
  node->right = temp;
}
