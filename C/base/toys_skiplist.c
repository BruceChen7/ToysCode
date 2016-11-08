#include "toys_skiplist.h"
#include <stdlib.h>
#include "toys_mem.h"

toys_skip_list_node* toys_sl_create_node(int level,double score, void *value)
{
    toys_skip_list_node* sl_node = TOYS_ALLOC(sizeof(*sl_node) + level*sizeof(struct toys_skip_list_level));
    
    sl_node->score = score;
    sl_node->value = value;
    return sl_node;
}



toys_skip_list* toys_sl_create(void)
{
    toys_skip_list *sl = TOYS_ALLOC(sizeof(*sl));
    sl->level = 1;
    sl->length = 0 ;
    sl->head  = toys_sl_create_node(TOYS_SKIP_LIST_MAX_LEVEL,0,NULL);

    int i;
    
    for(i = 0; i < TOYS_SKIP_LIST_MAX_LEVEL;i++)
    {
        sl->head->level[i].forward = NULL;
        sl->head->level[i].span = 0; 
    }
    sl->head->backward = NULL;
    sl->tail = NULL;
    
    return sl; 
}

void toys_sl_free_node(toys_skip_list_node *sl_node)
{
    TOYS_FREE(sl_node);
}

//return a random level for the new skip list  Node we are going to create
//the new level is between 1 to TOYS_SKIP_LIST_MAX_LEVEL (include TOYS_SKIP_LIST_MAX_LEVEL)
//
int  toys_sl_random_level(void)
{
    int level = 1;
    
    while((random() & 0xFFFF) < ( TOYS_SKIP_LIST_P * 0xffff))
        level += 1;
    return (level < TOYS_SKIP_LIST_MAX_LEVEL) ? level:TOYS_SKIP_LIST_MAX_LEVEL ;
}

void toys_sl_free_list(toys_skip_list *sl)
{
    toys_skip_list_node* node = sl->head->level[0].forward;
    toys_skip_list_node* next;

    while(node)
    {
        next = node->level[0].forward;
        TOYS_FREE(node);
        node = next;
    }
    TOYS_FREE(sl);
}

toys_skip_list_node* toys_sl_insert(toys_skip_list *sl,double score,void *value)
{
    unsigned int  rank[TOYS_SKIP_LIST_MAX_LEVEL]; 
    toys_skip_list_node* x= sl->head;
    toys_skip_list_node *update[TOYS_SKIP_LIST_MAX_LEVEL];

    int i = TOYS_SKIP_LIST_MAX_LEVEL - 1; 
    
    for(;i >= 0; i--)
    {
        rank[i] = (i == TOYS_SKIP_LIST_MAX_LEVEL-1) ?  0 : rank[i+1]; 

        while(x->level[i].forward && 
                (x->level[i].forward->score < score 
                 || x->level[i].forward->score == score 
                 && *(x->level[i].forward->value) < *value))
        {
            
            x = x->level[i].forward;
            rank[i] += x->level[i].span; 
        } 
        //reserve the new Node's forward pointer
        update[i] = x;
    }

    int level = toys_sl_random_level();

    if(level > sl->level)
    {
        for(i = sl->level ; i > level ; i++)
        {
            rank[i] = 0;
            update[i] = sl->head;
            update[i]->level[i].span = sl->length;
        }
        sl->level = level; 
    }

    //insert the new Node into the skip_list
    x = toys_sl_create_node(level,score,value);
    
    for(i = 0 ;i < level; i++)
    {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;

        x->level[i].span = update[i]->level[i].span-(rank[0] - rank[i]);
        update[i]->level[i].span = rank[0] - rank[i] + 1; 
    }

    for( i = level; i < sl->level; i++)
    {
        update[i]->level[i].span++; 
    }
    
    x->backward = (update[0]->level[0] ==sl->head ? NULL:update[0]);

    if(x->level[0].forward)
        x->level[0].forward->backward = x;
    else 
        sl->tail = x;
    sl->length++;
    return x; 
}

void toys_sl_delete_node(toys_skip_list* sl, toys_skip_list_node* node)
{

}
