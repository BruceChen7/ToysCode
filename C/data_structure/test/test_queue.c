#include <criterion/criterion.h>
#include "../queue.h"

Test(Queue,QueueMacroTest)
{
    struct QueueItem
    {
        int value;
        QUEUE_ENTRY(elem) entry; 
    };
   
    struct QueueItem *item;
    QUEUE_HEAD(,QueueItem) *TestHead;


    struct Queue_item*  test;
    QUEUE_HEAD(TestHead,elem);
    QUEUE_INSERT_TAIL(TestHead,item,entry);



}

