#include "vec.h"

#include <stdlib.h>

#include "toys_utils.h"

Vec*
createVec() {
    Vec* vec = (Vec*)(malloc(sizeof(*vec)));
    CHECK(vec, "allocated memory error");
    vec->capacity = 0;
    vec->size = 0;
    vec->dup = NULL;
    vec->free = NULL;
    vec->match = NULL;
    vec->arr = NULL;
    return vec;
}

static
void checkVec(Vec* vec) {
    CHECK(vec, "vec can't be null");
    CHECK(vec->size <= vec->capacity, "size can not be larger than capacity");
    if (vec->dup) {
        CHECK(vec->free, "dup member not null, but free memeber null");
        return;
    }
    CHECK(!(vec->free), "dup null, but free not null");
}

static uint32_t
getExpandSize(uint32_t capacity) {
    if (capacity == 0) {
        return 1;
    }
    return capacity << 1;
}

void
pushBack(Vec* vec, void* value) {
    CHECK(vec, "can't be NULL");
    checkVec(vec);
    if (vec->capacity <= vec->size) {
        uint32_t new_size = getExpandSize(vec->capacity);
        void** new_arr = (void **)malloc(sizeof(void*) * new_size);
        for (uint32_t i = 0; i < vec->size; ++i) {
            void* copy_elem = NULL;
            if (vec->dup) {
                copy_elem  = vec->dup(vec->arr[i]);
            } else {
                copy_elem = vec->arr[i];
            }
            new_arr[i] = copy_elem;
        }

        // 删除以前的元素
        for (uint32_t i = 0; i < vec->size; ++i) {
            if (vec->free) {
                vec->free(vec->arr[i]);
            }
        }
        free(vec->arr);
        vec->arr = new_arr;
        vec->capacity = new_size;
    }

    if (vec->dup) {
        vec->arr[vec->size++] = vec->dup(value);
    } else {
        vec->arr[vec->size++] = value;
    }
}


void
freeVec(Vec* vec) {
    checkVec(vec);
    if (vec->free) {
        for (uint32_t i = 0; i < vec->size; ++i) {
            vec->free(vec->arr[i]);
        }
    }
    free(vec->arr);
    free(vec);
}

void*
indexVec(Vec* vec, uint32_t i) {
    CHECK(i < vec->size, "index i larger than vec->size");
    checkVec(vec);
    return vec->arr[i];
}

int32_t
findInVec(Vec* vec, void* data) {
    checkVec(vec);
    if (!vec->arr) {
        return 0;
    }

    for (uint32_t i = 0; i < vec->size; ++i) {
        if (vec->match) {
            if (vec->match(vec->arr[i], data)) {
                return 1;
            }
        } else {
            if (vec->arr[i] == data) {
                return 1;
            }
        }
    }
    return 0;
}

