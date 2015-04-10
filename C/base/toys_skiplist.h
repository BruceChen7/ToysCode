#ifndef __TOYS__SKIPLIST_H__
#define __TOYS__SKIPLIST_H__

#define TOYS_SKIP_LIST_MAX_LEVEL 32
#define TOYS_SKIP_LIST_P 0.25

typedef struct toys_skip_list_node {
    void *value;
    double score;
    struct toys_skip_list_node *backward; 

    //flexible array
    struct toys_skip_list_level { 
        struct toys_skip_list_node *forward;
        unsigned int span; 
    }level[]; 
}toys_skip_list_node;


typedef struct toys_skip_list { 
    struct toys_skip_list_node *head;
    struct toys_skip_list_node *tail; 
    // the node number
    unsigned long length; 
    //the most level the skip list has
    int level; 
} toys_skip_list;

toys_skip_list_node* toys_sl_create_node(int level,double score,void *value); 

toys_skip_list *toys_sl_create(void);

void toys_sl_free_node(toys_skip_list_node *node);

void toys_sl_free_list(toys_skip_list *sl);

toys_skip_list_node *toys_sl_insert(toys_skip_list *sl,double score, void *value);

void toys_sl_delete_node(toys_skip_list* sl,toys_skip_list_node *x,toys_skip_list_node **update);

#endif
