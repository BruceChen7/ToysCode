#ifndef __TOYS_LIST_H__
#define __TOYS_LIST_H__

typedef struct toys_list_node {
	struct toys_list_node *prev;
	struct toys_list_node *next; 
	void *value; 
}toys_list_node;

typedef struct toys_list {
	toys_list_node* head;
	toys_list_node* tail;
	unsigned long len;
	void *(*dup)(void *ptr);
	void (*free)(void *ptr); 
	int (*match)(void *ptr,void *key); 
}toys_list;

//create a list
toys_list* toys_list_create(void);

//free the whole list
void toys_list_release(toys_list *list); 

toys_list* toys_list_add_node_head(toys_list *list,void *value); 

toys_list* toys_list_add_node_tail(toys_list *list,void *value); 

toys_list* toys_list_insert_node(toys_list *list, toys_list_node *old_node, void *value,int pos); 

//delete the specified node from the specified list
void  toys_list_del_node(toys_list *list,toys_list_node *node); 


toys_list_node* toys_list_index(toys_list* list,long index);
toys_list_node* toys_list_search_key(toys_list *list,void *key);

// void toys_list_print(toys_list *list);
#endif 
