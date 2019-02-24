#ifndef __TOYS_MEM_H__
#define __TOYS_MEM_H__

#include <pthread.h>
#include <string.h>
#include <stdint.h>

#include "base/toys_list.h"
#include "base/vec.h"

#define MAX_MEM_BLOCK 16
#define KILO_BYTES  1024
#define MEBI_BYTES  1024 * 1024

typedef struct MemPool {
    List* block_list[MAX_MEM_BLOCK];
} MemPool;

void memPoolInit();

void* memPoolAlloc(uint32_t bytes);

void memPoolFree(void* p);

void memPoolDestroy();

#endif
