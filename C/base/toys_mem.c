#include "toys_mem.h"

#include <stdlib.h>

#include "minunit.h"
#include "mutex.h"
#include "toys_list.h"
#include "toys_utils.h"

typedef struct MemBlock {
    char magic_header[2];
    int32_t in_use; // 是否在用
    uint32_t allocated_size;
    void* data;
} MemBlock;

#define MAX_ALLOC_SIZE ((2 << (MAX_MEM_BLOCK - 1)) * KILO_BYTES)
#define MAX_CACHED_BLOCK 16

static void
initMemBlock(MemBlock* b) {
    b->magic_header[0] = 'M';
    b->magic_header[1] = 'A';
    b->in_use = 0;
    b->allocated_size = 0;
    b->data = NULL;
}

static uint32_t
getPromoteSize(uint32_t total_size) {
    if (total_size > MAX_ALLOC_SIZE) {
        return total_size;
    }

    uint32_t size = KILO_BYTES;

    for (uint32_t i = 1; i < MAX_MEM_BLOCK; ++i) {
        if (size >= total_size) {
            size = i * KILO_BYTES;
            break;
        }
    }
    return size;
}

static MemBlock*
createMemBlock(uint32_t total_size) {
    uint32_t alloc_size = total_size + sizeof(MemBlock);
    MemBlock* block = (MemBlock*)malloc(alloc_size);
    initMemBlock(block);
    int32_t offset = OFFSETOF(MemBlock, data);
    block->data = ((char *)block + sizeof(MemBlock));
    block->allocated_size = getPromoteSize(total_size);
    block->in_use = 1;
    return block;
}

static MemPool* kMemInUse = NULL;

void
memPoolInit() {
    if (!kMemInUse) {
        kMemInUse = (MemPool*)malloc(sizeof(MemPool));
        for (uint32_t i = 0; i < MAX_MEM_BLOCK; ++i) {
            kMemInUse->block_list[i] = createList();
            kMemInUse->block_list[i]->free = free;
        }
    }

}

static uint32_t
getBlockIndex(uint32_t bytes) {
    uint32_t size = KILO_BYTES;
    if (size >= bytes) {
        return 0;
    }
    for (uint32_t i = 1; i < MAX_MEM_BLOCK; ++i) {
        size *= 2;
        if (size >= bytes) {
            return i;
        }
    }
    CHECK(0 == 1, "reach invalid path");
    return 0;
}

void *
memPoolAlloc(uint32_t bytes) {
    if (bytes == 0) {
        return NULL;
    }

    if (bytes > MAX_ALLOC_SIZE) {
        MemBlock* block = createMemBlock(bytes);
        return block->data;
    }
    uint32_t index = getBlockIndex(bytes);
    CHECK(index >= 0 && index < MAX_MEM_BLOCK, "invalid index");
    CHECK(kMemInUse != NULL, "kMemInUse must be init, call memPoolInit first");
    List* list = kMemInUse->block_list[index];

    if (listEmpty(list)) {
        MemBlock* block = createMemBlock(bytes);
        return block->data;
    }

    MemBlock* b = (MemBlock *)list->head->value;
    CHECK(b->in_use == 0, "block is in use, that's wrong");
    CHECK(b->magic_header[0] == 'M', "magic header not right");
    CHECK(b->magic_header[1] == 'A', "magic header not right");

    b->in_use = 1;
    ListNode* head = list->head;
    releaseValueFromNode(list, head);
    return b->data;
}

void
memPoolFree(void* p) {
    int32_t offset = sizeof(MemBlock);
    MemBlock* b = (MemBlock*)((char *)p  - offset);

    CHECK(b->in_use == 1, "block must be used");

    uint32_t allocated_size = b->allocated_size;
    if (allocated_size > MAX_ALLOC_SIZE) {
        free(b);
        return;
    }
    uint32_t index = getBlockIndex(allocated_size);
    CHECK(index >= 0 && index < MAX_MEM_BLOCK, "not valid index");
    List* list = kMemInUse->block_list[index];
    // 如果已经有足够多的缓存
    if (list->len > MAX_CACHED_BLOCK) {
        free(b);
        return;
    }
    b->in_use = 0;
    addNodeToTail(list, b);
}

void
memPoolDestroy() {
    CHECK(kMemInUse != NULL, "can't be null");
    for (uint32_t i = 0; i < MAX_MEM_BLOCK; ++i) {
        freeList((kMemInUse->block_list)[i]);
    }
    free(kMemInUse);
    kMemInUse = NULL;
}
