#include "base/toys_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "base/minunit.h"

static void* dupNode(void* p) {
    int* int_p = (int *)(p);
    int* res = (int *)malloc(*int_p);
    *res = *int_p;
}

static void freeNode(void* p) {
    free(p);
}

static int matchNode(void* m, void* n) {
    return *(int *)(m) == *(int *)(n);
}


// https://github.com/siu/minunit
MU_TEST(appendToHead) {
    List* list = createList();
    list->dup = dupNode;
    list->free = freeNode;
    list->match = matchNode;
    int a = 1;
    addNodeToHead(list, &a);
    int b = 2;
    mu_check(1 == list->len);
    addNodeToHead(list, &b);
    mu_check(list->len == 2);
    mu_check(*(int *)(list->head->value) == 2);
    mu_check(*(int *)(list->tail->value) == 1);
    freeList(list);
}

MU_TEST_SUITE(list_suite) {
    MU_RUN_TEST(appendToHead);
}


int main(int argc, char* argv[]) {
    MU_RUN_SUITE(list_suite);
    MU_REPORT();
    return minunit_status;
}
