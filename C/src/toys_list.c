#include "toys_list.h"
#include <stdlib.h>

toys_list* toys_list_create(void)
{
	struct toys_list* list;
	
	if((list = malloc(sizeof(*list))) == NULL)
		return NULL;

	list->head = list->tail = NULL;
	list->len = 0;
	list->dup = NULL;
	list->free = NULL;
	list->match = NULL;
	return list; 
}

// free the whole the list
void toys_list_release(toys_list *list)
{
 	unsigned long len = list->len;
	toys_list_node *cur, *next;
	cur  = list->head;
	
	while(len--)
	{
		next = cur->next;

		if(list->free)
			list->free(cur->value);
		//delete the node
		free(cur);
		cur = next;
	}

	free(list); 
}

toys_list *toys_list_add_node_head(toys_list *list,void *value)
{
	toys_list_node *node;

	if((node = malloc(sizeof(*node))) == NULL)
		return NULL;

	node->value = value;

	if(list->len == 0)
	{
		list->head  = list->tail = node;
		node->prev = node->next = NULL;

	}
	else
	{
		node->prev = NULL;
		node->next = list->head;
		list->head->prev = node;
		list->head = node; 
	}

	list->len++;
	return list; 
}

toys_list *toys_list_add_node_tail(toys_list *list,void *value)
{
	toys_list_node *node = malloc(sizeof(*node)) ;

	if(node == NULL)
		return NULL;

	node->value = value;

	if(list->len  == 0)
	{
		list->tail = list->head = node;
		node->prev = node->next = NULL;
	}
	else
	{
		node->prev = list->tail;
		list->tail->next = node;
		node->next = NULL;
		list->tail = node;
	}

	list->len++; 
	return list;

}

toys_list *toys_list_insert_node(toys_list* list,toys_list_node* old_node,void *value,int pos)
{
	toys_list_node *node = malloc(sizeof(*node));
	
	if(node == NULL)
		return NULL;
	
	node->value = value;
	
	if(pos == 0) 
	{
		list->head->prev = node;
		node->next = list->head;
		node->prev = NULL;
		
	}



}
