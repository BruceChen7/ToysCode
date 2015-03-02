#include "toys_list.h"
#include "toys_utils.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * On error, NULL is returned 
 * On Success,new 'struct toys_list *' pointer is returned 
 */ 
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

/*
 * add a new node to the head of the list
 *
 * On error,NULL is returned and no operation is performed
 *
 * On success, the 'list' pointer you pass to the function is returned
 * 
 * */
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

void toys_list_del_node(toys_list *list, toys_list_node *node)
{
	if(node->prev != NULL)
		node->prev->next = node->next;
	else 
	/* if node is the first 'list node' */
		list->head = node->next; 

	if(node->next !=NULL)
		node->next->prev = node->prev;
	else
		/* if node is the last 'list node' */
		list->tail = node->prev;

	if(list->free)
		list->free(node->value);
	free(node);
	list->len--; 
}

//support the negative index
// eg : toys_list_index(list, -1) return the pointer of last element of the list;
toys_list_node* toys_list_index(toys_list *list, long index)
{

	toys_list_node *node = NULL;
	long len = list->len;
	int i = index; 
	node = index >= 0 ? list->head:list->tail;

	if(i >= 0)
	{
		while(i--)	
		{
			node = node->next;
		} 
	}
	else 
	{
		while(++i)
		{
			node = node->prev;
		}
	}
	return node; 
}

toys_list_node* toys_list_search_key(toys_list *list,void *key)
{
	toys_list_node *node = list->head;
	unsigned long len = list->len; 

	while(len--)
	{
		if(list->match)
		{
			if(list->match(node->value,key))
			{
				return node;
			}
		}
		else if(key == node->value)
		{
			return node; 
		}
		node = node->next; 
	}

	if(len == 0)
		return NULL;

}

