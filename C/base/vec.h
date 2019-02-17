#ifndef __BASE_VEC_H__
#define __BASE_VEC_H__
#include <stdint.h>

typedef struct Vec {
    uint32_t size;
    uint32_t capacity;
    void* (*dup)(void* p);
    void (*free)(void* p);
    int32_t (*match)(void* m, void* n);
    void** arr;
} Vec;


Vec* createVec();

void* indexVec(Vec* vec, uint32_t i);

void pushBack(Vec* vec, void* value);

void freeVec(Vec* vec);

#endif
