#include "binary_tree.h"
struct node* creat_new_node(int data)
{   
    struct node *new_node = malloc(sizeof(*new_node));
    
    if(new_node == NULL)
        fprintf(stderr,"can't creat a new node\n");
    new_node->value = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void print_in_order(struct node *root)
{
    if(root != NULL)
    {
        print_in_order(root->left);
        fprintf(stdout,"%d ",root->value);
       
        print_in_order(root->right);
    }
    
}

struct node* remove_half_leaf(struct node* root)
{
    if(root == NULL)
        return NULL;
    root->left = remove_half_leaf(root->left);
    root->right = remove_half_leaf(root->right);

    if(root->left == NULL && root->right == NULL)
        return root;

    if(root->left == NULL)
    {
       struct node *new_node = root->right;
       free(root); 
       return new_node;
    }
    if(root->right == NULL)
    {
       struct node *new_node = root->left; 
       free(root);
       return new_node; 
    }
    return root; 
}
