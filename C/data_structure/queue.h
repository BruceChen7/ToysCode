#ifndef __QUEUE_H_
#define __QUEUE_H_


//队列的头,
//用来管理队列
#define QUEUE_HEAD(name, type) \
struct name {                  \
    struct type *first;        \
    struct type *last;        \
}

#define QUEUE_ENTRY(type) \
struct                    \
{                         \
   struct type* prev;     \
   struct type* next;     \
}


//获取队列头
#define QUEUE_FIRST(head) ((head)->first)
#define QUEUE_END(head) NULL
#define QUEUE_LAST(head)((head)->last)

//判断当前的队列是否为空
#define IS_QUEUE_EMPTY(head) (QUEUE_FIRST(head) == QUEUE_END(head) )

#define QUEUE_INIT(head) do \
{                           \
    head->first = NULL;     \
    head->last = NULL;      \
}while(0)

#define QUEUE_INSERT_TAIL(head,elem,field) do { \
    (elem)->field.next = NULL;                  \
    (elem)->field.prev = (head)->last;          \
    (head)->field.next = (elem)                 \
    (head)->last = (elem);                      \
}while(0)

#endif
