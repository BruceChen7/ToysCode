#ifndef __TOYS_UTILS_H__
#define __TOYS_UTILS_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

void systemCall(int32_t error_code, const char* msg) {
    if (error_code != 0) {
        printf("%s\n", msg);
        abort();
    }
}

#define CHECK(test, msg) MU__SAFE_BLOCK( \
    if (!(test)) { \
        printf("function %s, line %d : %s\n", __FUNCTION__, __LINE__, msg); \
        abort(); \
    })
#endif
