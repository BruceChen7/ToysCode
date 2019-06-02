#include "toys_list.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void
systemCall(int32_t error_code, const char* msg) {
    if (error_code != 0) {
        printf("%s\n", msg);
        abort();
    }
}

uint32_t getLogiCpuNum() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}


