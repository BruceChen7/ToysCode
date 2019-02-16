#ifndef __TOYS_LIST_H__
#define __TOYS_LIST_H__

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    void *value;
} ListNode;

typedef struct List {
    ListNode* head;
    ListNode* tail;
    unsigned long len;
    void* (*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);
} List;

// create a list
List* createList(void);

// free the whole list
void freeList(List* list);

List* addNodeToHead(List* list, void *value);

List* addNodeToTail(List* list, void *value);

List* insertNodeBefore(List* list, ListNode *old_node, void *value,int pos);

void deleteNode(List *list, ListNode *node);

// find the common node which both the lists have
ListNode* findCommonNode(List *list1,List *list2);

ListNode* indexList(List* list, long index);

ListNode* searchKey(List *list, void *key);

#endif
