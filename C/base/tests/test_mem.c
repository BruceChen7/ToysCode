#include "base/toys_mem.h"
#include <stdio.h>

#include "base/minunit.h"
#include "base/toys_utils.h"

void testOneByte() {
    memPoolInit();
    char* p = (char *)memPoolAlloc(1);
    CHECK(p != NULL, "can not be null");
    *p = 'c';
    printf("%c\n", *p);
    memPoolFree(p);
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
    testLarger();
    return 0;
}
