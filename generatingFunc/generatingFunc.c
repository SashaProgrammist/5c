#include "generatingFunc.h"

int getRand(){
    static long long result = 0;
    result = (result << 7) + (result << 9) + (result >> 13) + 1;
    return (int)result;
}

void generateRandomArray(int *array, size_t size) {
    for (int i = 0; i < size; ++i)
        *(array++) = getRand() % 1000;
}

void generateOrderedArray(int *array, size_t size) {
    for (int i = 0; i < size; ++i)
        *(array++) = i;
}

void generateOrderedBackwards(int *array, size_t size) {
    for (int i = (int)size; i >= 0; --i)
        *(array++) = i;
}
