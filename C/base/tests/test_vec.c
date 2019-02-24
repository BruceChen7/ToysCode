#include "base/vec.h"
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

Vec* vec_with_dup = NULL;
Vec* vec = NULL;

void
test_setup() {
    vec_with_dup = createVec();
    vec_with_dup->dup = dupNode;
    vec_with_dup->free = freeNode;
    vec_with_dup->match = matchNode;
    mu_check(vec_with_dup);
    vec = createVec();
    mu_check(vec);
}

void
test_teardown() {
    freeVec(vec_with_dup);
    freeVec(vec);
}

MU_TEST(vecInit) {
    mu_check(vec);
    mu_check(vec->size == 0);
    mu_check(vec->capacity == 0);
}

MU_TEST(vecPushback) {
    int a  = 0;
    pushBack(vec, &a);
    mu_check(vec->size == 1);
    mu_check(vec->capacity == 1);

    void* b = indexVec(vec, 0);
    mu_check(*(int *)(b) == 0);

    pushBack(vec, &a);
    void* c = indexVec(vec, 1);
    mu_check(*(int *)(c) == 0);

    mu_check(vec->size == 2);
    mu_check(vec->capacity == 2);

    int d = 3;
    pushBack(vec, &d);

    void* e = indexVec(vec, 2);
    mu_check(*(int *)(e) == 3);
    mu_check(vec->size == 3);
    mu_check(vec->capacity == 4);

    mu_check(findInVec(vec, e) == 1);
}

static int32_t matchInt(void* a, void* b) {
    return *(int *)a == *(int *)b;
}
MU_TEST(findInVecTest) {
    int a = 0;
    pushBack(vec, &a);
    mu_check(vec->size == 1);
    mu_check(vec->capacity == 1);

    vec->match = matchInt;
    int b = 0;

    mu_check(findInVec(vec, &b) == 1);

    int c = 1;

    mu_check(findInVec(vec, &c) == 0);

    vec->match = NULL;
    mu_check(findInVec(vec, &b) == 0);
    mu_check(findInVec(vec, &a) == 1);

}
MU_TEST_SUITE(vec_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(vecInit);
    MU_RUN_TEST(vecPushback);
    MU_RUN_TEST(findInVecTest);
}

int main() {
    MU_RUN_SUITE(vec_suite);
    MU_REPORT();
    return minunit_status;
}


