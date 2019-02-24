#include "base/toys_mem.h"
#include <stdio.h>

#include "base/minunit.h"
#include "base/toys_utils.h"

void
test_setup() {
    memPoolInit();
}

void
test_teardown() {
    memPoolDestroy();
}

MU_TEST(allocateLargeMem) {
    void* p = memPoolAlloc(128 * 1024 * 1024);
    CHECK(p != NULL, "can not be null");
    memPoolFree(p);
}

MU_TEST_SUITE(mem_suite) {
    MU_RUN_TEST(allocateLargeMem);
}

int main() {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_SUITE(mem_suite);
    MU_REPORT();
    return minunit_status;
}
