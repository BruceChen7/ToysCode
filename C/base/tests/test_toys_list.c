#include "base/toys_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "base/minunit.h"

static void*
dupNode(void* p) {
    int* int_p = (int *)(p);
    int* res = (int *)malloc(sizeof(int));
    *res = *int_p;
    return res;
}

static void
freeNode(void* p) {
    free(p);
}

static int
matchNode(void* m, void* n) {
    return *(int *)(m) == *(int *)(n);
}


static List* list;

// 每个test都会重新调用一次
void
test_setup() {
    list = createList();
    list->dup = dupNode;
    list->free = NULL;
    list->match = matchNode;
    mu_check(list);
}

void
test_teardown() {
    freeList(list);
}

// https://github.com/siu/minunit
MU_TEST(appendToHead) {
    int a = 1;
    addNodeToHead(list, &a);
    mu_check(*((int *)(list->head->value)) == 1);
    mu_check(*(int *)(list->tail->value) == 1);
    int b = 2;
    mu_check(1 == list->len);
    addNodeToHead(list, &b);
    mu_check(list->len == 2);
    mu_check(*(int *)(list->head->value) == 2);
    mu_check(*(int *)(list->tail->value) == 1);
    int c = 3;
    addNodeToHead(list, &c);
    mu_check(3 == list->len);
    mu_check(*(int *)(list->head->value) == 3);
    mu_check(*(int *)(list->head->next->value) == 2);
    mu_check(*(int *)(list->tail->value) == 1);
}

MU_TEST(emptyList) {
    mu_check(list->len == 0);
    mu_check(list->head == NULL);
    mu_check(list->tail == NULL);
}

MU_TEST(oneNodeList) {
    int val = 0;
    addNodeToHead(list, &val);
    mu_check(list->len == 1);
    mu_check(*(int *)(list->head->value) == 1);
    mu_check(*(int *)(list->tail->value) == 1);
}

MU_TEST(appendToTail) {
    int a = 3;
    addNodeToTail(list, &a);
    mu_check(*(int *)(list->tail->value) == 3);
    mu_check(list->len == 1);
    mu_check(*(int *)(list->head->value) == 3);
}

MU_TEST(deleteNodeInList) {
    int a = 1;
    addNodeToHead(list, &a);
    int b = 2;
    addNodeToHead(list, &b);
    int c = 3;
    addNodeToHead(list, &c);

    // 查找2，然后删掉
    ListNode* node = indexList(list, 1);
    deleteNode(list, node);

    mu_check(list->len == 2);
    mu_check(*(int *)(list->head->value) == 3);
    mu_check(*(int *)(list->tail->value) == 1);

    // 查找位置0的节点，并删除掉
    node = indexList(list, 0);
    deleteNode(list, node);

    mu_check(list->len == 1);
    mu_check(*(int *)(list->head->value) == 1);
    mu_check(*(int *)(list->tail->value) == 1);

    node = indexList(list, 0);
    deleteNode(list, node);

    mu_check(list->len == 0);
    mu_check(list->head == NULL);
    mu_check(list->tail == NULL);
}

MU_TEST(searchNodeInList) {
}

MU_TEST_SUITE(list_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(appendToHead);
    MU_RUN_TEST(appendToTail);
    MU_RUN_TEST(emptyList);
    MU_RUN_TEST(deleteNodeInList);
    MU_RUN_TEST(searchNodeInList);
}

int
main(int argc, char* argv[]) {
    MU_RUN_SUITE(list_suite);
    MU_REPORT();
    return minunit_status;
}
