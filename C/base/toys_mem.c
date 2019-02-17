#include "toys_mem.h"

#include <stdlib.h>

#include "minunit.h"
#include "mutex.h"
#include "toys_list.h"
#include "toys_utils.h"

typedef struct MemBlock {
    char magic_header[2];
    int32_t in_use; // 是否在用
    void* data;
} MemBlock;

static void
initMemBlock(MemBlock* b) {
    b->magic_header[0] = 'M';
    b->magic_header[1] = 'A';
    b->in_use = 0;
    b->data = NULL;
}

static MemBlock*
createMemBlock(uint32_t total_size) {
    MemBlock* block = (MemBlock*)malloc(sizeof(*block));
    initMemBlock(block);
    block->data = malloc(sizeof(total_size));
    return block;
}


static MemPool* kMemInUse = NULL;

MemPool*
memPoolInit() {
    if (!kMemInUse) {
        return kMemInUse;
    }

    kMemInUse = (MemPool*)malloc(sizeof(MemPool));

    for (uint32_t i = 0; i < MAX_MEM_BLOCK; ++i) {
        kMemInUse->block_list[i] = createList();
        kMemInUse->block_list[i]->free = free;
    }

    kMemInUse->allocated_chunk = createVec();

    return kMemInUse;
}

static uint32_t getBlockIndex(uint32_t bytes) {
    uint32_t i = 0;
    for (i = 1; i <= MAX_MEM_BLOCK; ++i) {
        if (2 * i * KILO_BYTES >= bytes) {
            return i - 1;
        }
    }
    CHECK(0 == 1, "reach invalid path");
    return -1;
}

void*
memPoolAlloc(uint32_t bytes) {
    if (bytes == 0) {
        return NULL;
    }

    if (bytes > (2 >> MAX_MEM_BLOCK)) {
        return malloc(bytes);
    }
    uint32_t index = getBlockIndex(bytes);
    CHECK(index >= 0 && index < MAX_MEM_BLOCK, "invalid index");
    CHECK(kMemInUse != NULL, "kMemInUse must be init, call memPoolInit first");
    List* list = (kMemInUse->block_list)[index];

    if (listEmpty(list)) {
        return malloc(bytes);
    }

    MemBlock* b = (MemBlock *)list->head->value;
    CHECK(b->in_use == 0, "block in use, that's wrong");
    CHECK(b->magic_header[0] == 'M', "magic header not right");
    CHECK(b->magic_header[1] == 'A', "magic header not right");
    return list->head->value;
}

void
memPoolFree(void* p) {
    CHECK(kMemInUse->allocated_chunk, "allocated_chunk can not be null, call memPoolInit first");

    if (findInVec(kMemInUse->allocated_chunk, p)) {

    }
}
