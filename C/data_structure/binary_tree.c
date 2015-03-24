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


struct node* bst_insert(struct node *root, int data)
{
    if(root == NULL)
        return creat_new_node(data);

    else if(data < root->value)
    {
        root->left = bst_insert(root->left,data);
    }
    else 
        root->right = bst_insert(root->right,data);
    return root;
}

int get_binary_tree_depth(struct node* root)
{
    int depth;
    if(root == NULL)
        return 0;
    else 
    {
        int left_depth = get_binary_tree_depth(root->left) + 1;
        int right_depth = get_binary_tree_depth(root->right) + 1; 

        depth = (left_depth > right_depth) ? left_depth : right_depth;
        
    }
    return depth; 
}

void  kth_largetst_node_for_bst_uitl(struct node *root,int k, int *cnt,struct node **kth_node)
{

    if(root == NULL  ||  *cnt >= k)
    {
        return ;
    }

    kth_largetst_node_for_bst_uitl(root->right,k,cnt,kth_node);

    (*cnt)++;
    
    if(*cnt == k)
    {

        *kth_node = root;
        return ; 
    }

    kth_largetst_node_for_bst_uitl(root->left,k,cnt,kth_node);
 
    
}

struct node*  kth_largetst_node_for_bst(struct node *root, int k)
{ 
    int cnt = 0;
    struct node * kth_node  = NULL;
    
    kth_largetst_node_for_bst_uitl(root,k,&cnt,&kth_node); 


    return kth_node; 
}

