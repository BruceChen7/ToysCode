#include "base/toys_list.h"

#include <stdio.h>
#include <stdlib.h>

#include "base/minunit.h"

static void*
dupNode(void* p) {
    int* int_p = (int *)(p);
    int* res = (int *)malloc(sizeof(int));
    *res = *int_p;
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
    list->free = freeNode;
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
    mu_check(*(int *)(list->head->value) == 1);
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

MU_TEST(appendToTail) {
    int a = 3;
    addNodeToTail(list, &a);
    mu_check(*(int *)(list->tail->value) == 3);
    mu_check(list->len == 1);
    mu_check(*(int *)(list->head->value) == 3);
}

MU_TEST_SUITE(list_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(appendToHead);
    MU_RUN_TEST(appendToTail);
}


int
main(int argc, char* argv[]) {
    MU_RUN_SUITE(list_suite);
    MU_REPORT();
    return minunit_status;
}
