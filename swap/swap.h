#ifndef PROJECT_SWAP_H
#define PROJECT_SWAP_H

#include <stdlib.h>
#include <memory.h>
#include <malloc.h>

#include "../compare/compare.h"
#include "../test/test.h"

typedef struct SwapFunc{
    void (* swap)(void *, void *, size_t);
    char name[64];
}SwapFunc;

// количество байт при котором
// time(swapForInt) == time(swapMem)
#define INFLECTION 0 // -11~

#define SWAP_INT(a, b) swapInt(a, b, 0)
#define SWAP_CHAR(a, b) swapChar(a, b, 0)
#define SWAP(a, b) swap(a, b, sizeof(*(a)))

#define COUNT_SWAP (*getCountSwap())
size_t *getCountSwap();

#define SWAP_BYT (*getSwapByt())
size_t *getSwapByt();

void swap(void *a, void *b, size_t sizeBat);

void swapInt(void *a, void *b, size_t sizeBat);

void swapChar(void *a, void *b, size_t sizeBat);

void swapMem(void *a, void *b, size_t sizeBat);

void swapForInt(void *a, void *b, size_t sizeBat);

#endif //PROJECT_SWAP_H
