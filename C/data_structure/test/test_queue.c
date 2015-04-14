#include <criterion/criterion.h>
#include "../queue.h"
#include <assert.h>
#include <stdlib.h>
Test(Queue,QueueMacroTest)
{
    struct QueueNode
    {
        int value;
        QUEUE_ENTRY(QueueNode) entry; 
    };
   
    struct QueueNode *node = malloc(sizeof(*node));  
    node->entry.prev = NULL;

    QUEUE_HEAD(QueueList,QueueNode) *TestHead = malloc(sizeof(*TestHead));

    QUEUE_INIT_HEAD(TestHead);

    assert(TestHead->first == NULL);
    assert(TestHead->last == NULL);

    node->value = 1; 
    QUEUE_INSERT_TAIL(TestHead,node,entry);

    struct QueueNode *another_node = malloc(sizeof(*another_node));
    another_node->value = 2;

    QUEUE_INSERT_TAIL(TestHead,another_node,entry);

    assert_eq(TestHead->last->value,2);

    free(TestHead);
    free(node);
}

