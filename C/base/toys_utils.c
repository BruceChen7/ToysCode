#include "toys_list.h"
#include <stdio.h>
#include <stdlib.h>

void
systemCall(int32_t error_code, const char* msg) {
    if (error_code != 0) {
        printf("%s\n", msg);
        abort();
    }
}
