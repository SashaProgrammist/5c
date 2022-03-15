#include "compare.h"

int compare_int(int a, int b){
    if (isLess(a, b)) return 1;
    if (isLarge(a, b)) return -1;
    return 0;
}

int compare_size_t(size_t a, size_t b) {
    COUNT_COMPARE++;
    if (a < b) return 1;
    COUNT_COMPARE++;
    if (a > b) return -1;
    return 0;
}

size_t *getCountCompare() {
    static size_t countCompare = 0;
    return &countCompare;
}

bool isLess(int a, int b) {
    COUNT_COMPARE++;
    return a < b;
}

bool isLessOrEqual(int a, int b) {
    COUNT_COMPARE++;
    return a <= b;
}

bool isEqual(int a, int b) {
    COUNT_COMPARE++;
    return a == b;
}

bool isEqualOrLarge(int a, int b) {
    COUNT_COMPARE++;
    return a >= b;
}

bool isLarge(int a, int b) {
    COUNT_COMPARE++;
    return a > b;
}
