#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H

#include<time.h>

#include "../sortFunc/sortFunc.h"
#include "../generatingFunc/generatingFunc.h"
#include "../compare/compare.h"
#include "../swap/swap.h"

#define MAX_SIZE 50
#define RESOLUTION_STRAIGHT_TIME_TEST 10000000

#define TEST(testCode, time, countCompare, countSwap, swapBat) { \
    clock_t start_time = clock();                                \
    COUNT_COMPARE = 0;                                           \
    COUNT_SWAP = 0;                                              \
    SWAP_BYT = 0;                                                \
                                                                 \
    testCode                                                     \
                                                                 \
    clock_t end_time = clock();                                  \
    clock_t sort_time = end_time - start_time ;                  \
    time = (double)sort_time / CLOCKS_PER_SEC ;                  \
    countCompare = COUNT_COMPARE;                                \
    countSwap = COUNT_SWAP;                                      \
    swapBat = SWAP_BYT;                                          \
}

#define TIME_TEST(testCode, time) { \
    size_t countSwap, countCompare, swapBat; \
    TEST(testCode, time, countCompare, countSwap, swapBat) \
}

#define STRAIGHT_TIME_TEST(testCode, time) {                \
    clock_t start_time = clock();                           \
    for (int i = 0; i < RESOLUTION_STRAIGHT_TIME_TEST; i++) \
        testCode                                            \
    clock_t end_time = clock();                             \
    clock_t sort_time = end_time - start_time ;             \
    time = (double)sort_time /                              \
        CLOCKS_PER_SEC /                                    \
        RESOLUTION_STRAIGHT_TIME_TEST;                      \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

#define COUNT_ERROR (*getCountError())
size_t *getCountError();

bool isOrdered(int *array, size_t size);

void outputArray_(int *array, size_t size);

void check(void (*sortFunc )(int *, size_t),
           void (*generateFunc )(int *, size_t),
           size_t size, char *experimentName);

void experiment_sortIndirect();

void experiment_swap(size_t shift, size_t maxSize);

void outputInFile(char fileName[],
                  char data[]);

#endif //PROJECT_TEST_H
