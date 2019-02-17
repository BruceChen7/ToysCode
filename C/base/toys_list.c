#include "toys_list.h"
#include "toys_utils.h"
#include "toys_mem.h"
#include <stdlib.h>
#include <stdio.h>

List*
createList(void) {
    struct List* list;

    if ((list = malloc(sizeof(*list))) == NULL) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->len = 0;
    list->dup = NULL;
    list->free = NULL;
    list->match = NULL;
    return list;
}

void
freeList(List* list) {
    unsigned long len = list->len;
    ListNode *cur, *next;
    cur = list->head;

    while (len--) {
        next = cur->next;

        if (list->free) {
            list->free(cur->value);
        }
        free(cur);
        cur = next;
    }

    free(list);
}

List*
addNodeToHead(List* list, void *value) {
    ListNode *node;

    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;

    if (list->dup) {
        node->value = list->dup(value);
    }


    if (list->len == 0) {
        list->head  = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

    list->len++;
    return list;
}

List*
addNodeToTail(List *list, void *value) {
    ListNode *node = malloc(sizeof(*node)) ;

    if (node == NULL) {
        return NULL;
    }

    if (list->dup)  {
        node->value = list->dup(value);
    }

    if (list->len == 0) {
        list->tail = list->head = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        node->next = NULL;
        list->tail = node;
    }

    list->len++;
    return list;
}


List*
insertNodeBefore(List* list, ListNode* old_node, void *value, int pos) {
    ListNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->value = value;

    if (pos == 0) {
        list->head->prev = node;
        node->next = list->head;
        node->prev = NULL;
    }
}

void
deleteNode(List *list, ListNode *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    else {
        list->head = node->next;
    }

    if (node->next !=NULL) {
        node->next->prev = node->prev;
    } else {
        /* if Node is the last 'list Node' */
        list->tail = node->prev;
    }

    if (list->free) {
        list->free(node->value);
    }
    free(node);
    list->len--;
}

ListNode*
indexList(List *list, uint32_t index) {

    ListNode *node = NULL;
    uint32_t len = list->len;
    uint32_t i = index;
    node = index >= 0 ? list->head : list->tail;

    if (i >= 0) {
        while(i--) {
            node = node->next;
        }
    }
    else {
        while (++i) {
            node = node->prev;
        }
    }
    return node;
}

ListNode*
searchKey(List* list, void* key) {
    ListNode *node = list->head;
    unsigned long len = list->len;

    if (len == 0) {
        return NULL;
    }
    while (len--) {
        if (list->match) {
            if (list->match(node->value, key)) {
                return node;
            }
        }
        else if (key == node->value) {
            return node;
        }
        node = node->next;
    }
}

ListNode*
findCommonNode(List *l1, List *l2) {
    int len1 = l1->len;
    int len2 = l2->len;

    //p_long_head is the head which has more nodes;
    ListNode* p_long_head = (len1 > len2 ? l1->head:l2->head);
    ListNode* p_short_head = (len1 < len2 ? l1->head:l2->head);

    int difflen = (len1 > len2 ? len1-len2 : len2-len1);

    ListNode* p_common_node = NULL;

    while (difflen--) {
        p_long_head = p_long_head->next;
    }

    while (p_long_head && p_short_head && p_long_head != p_short_head) {
        p_long_head = p_long_head->next;
        p_short_head = p_short_head->next;
    }

    if (p_long_head == p_short_head) {
        p_common_node = p_short_head;
    }
    return p_common_node;
}

int32_t listEmpty(List* list) {
    return (list->len == 0);
}

