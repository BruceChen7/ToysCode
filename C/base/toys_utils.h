#ifndef __TOYS_UTILS_H__
#define __TOYS_UTILS_H__

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

void systemCall(int32_t error_code, const char* msg);

#define CHECK(test, msg) MU__SAFE_BLOCK( \
    if (!(test)) { \
        printf("function %s, line %d : %s\n", __FUNCTION__, __LINE__, msg); \
        abort(); \
    })

// 获取便宜量
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

uint32_t getLogiCpuNum();

#endif






