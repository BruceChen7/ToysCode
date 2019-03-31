#ifndef __TOYS_LIST_H__
#define __TOYS_LIST_H__
#include <stdint.h>

typedef struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    void *value;
} ListNode;

typedef struct List {
    ListNode* head;
    ListNode* tail;
    uint32_t len;
    void* (*dup)(void *ptr);
    void (*free)(void *ptr);
    int (*match)(void *ptr, void *key);
} List;

// create a list
List* createList(void);

int32_t listEmpty(List* list);

// free the whole list
void freeList(List* list);

List* addNodeToHead(List* list, void *value);

List* addNodeToTail(List* list, void *value);

List* insertNodeBefore(List* list, ListNode *old_node, void *value,int pos);

// 删除节点，node对应的value也释放
void deleteNode(List *list, ListNode *node);

// 从链表中释放该节点，获取该节点的值。
void* releaseValueFromNode(List *list, ListNode *node);

// find the common node which both the lists have
ListNode* findCommonNode(List *list1, List *list2);

ListNode* indexList(List* list, uint32_t index);

ListNode* searchKey(List *list, void *key);

#endif
