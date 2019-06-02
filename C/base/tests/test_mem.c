#include "base/toys_mem.h"
#include <stdio.h>

#include "base/minunit.h"
#include "base/time.h"
#include "base/toys_utils.h"

void benchmarkMalloc() {
    long long start = 0, elapsed = 0;
    long long count = 10000000;
    for (uint32_t i = 0; i < count; i++) {
        void* p = malloc(1);
        CHECK(p != NULL, "can not be null");
        free(p);
    }
    endBenchMark("malloc benchmark");
}

void testOneByte() {
    memPoolInit();
    char* p = (char *)memPoolAlloc(1);
    CHECK(p != NULL, "can not be null");
    *p = 'c';
    printf("address %p, %c\n", p, *p);
    memPoolFree(p);

    char* old_p = (char *)memPoolAlloc(1);
    CHECK(p == old_p, "p not equal old_p");

    CHECK(old_p != NULL, "can not be null");
    *old_p = 'd';
    printf("address %p, %c\n", old_p, *old_p);
    memPoolFree(p);

    long long start, elapsed;
    startBenchMark();
    long long count = 10000000;
    for (uint32_t i = 0; i < count; i++) {
        void* p = memPoolAlloc(1);
        CHECK(p != NULL, "can not be null");
        memPoolFree(p);
    }
    endBenchMark("alloc benchmark");

    memPoolDestroy();
}

void testLarger() {
    memPoolInit();
    void* p = memPoolAlloc(128 * 1024 * 1024);
    CHECK(p != NULL, "can not be null");
    memPoolFree(p);
    memPoolDestroy();
}

int main() {
    testOneByte();
    benchmarkMalloc();
    testLarger();
    return 0;
}
