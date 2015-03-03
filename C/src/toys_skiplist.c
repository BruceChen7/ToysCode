#include "toys_skiplist.h"
#include "toys_mem.h"
#define TOYS_SKIP_LIST_MAX_LEVEL 1024

toys_skiplist_node* toys_sl_create_node(int level,double score, void *value)
{
	toys_skiplist_node* sl_node = TOYS_ALLOC(sizeof(*sl_node) + level*sizeof(struct toys_skiplist_level));
	
	sl_node->score = score;
	sl_node->value = value;
	return sl;
}



toys_skiplist* toys_sl_create(void)
{
	toys_skiplist *sl = TOYS_ALLOC(sizeof(*sl));
	sl->level = 1;
	sl-length = 0 ;
	sl->head  = toys_sl_create_node(TOYS_SKIP_LIST_MAX_LEVEL,0,NULL);

	int i;
	
	for(i = 0; i < TOYS_SKIP_LIST_MAX_LEVEL,i++)
	{
		sl->head->level[i].forward = NULL;
		sl->head->level[i].span = 0; 
	}
	sl->head->backward = NULL;
	sl->tail = NULL;
	
	return sl; 
}

void toys_sl_free_node(toys_skiplist_node *sl_node)
{
	TOYS_FREE(sl_node);
}

void toys_sl_free_list(toys_skiplist *sl)
{
	toys_skiplist_node* node = sl->head->level[0].forward,*next;

	while(node)
	{
		next = node->level[0]->forward;
		TOYS_FREE(node);
		node = next;
	}
	TOYS_FREE(sl);
}
