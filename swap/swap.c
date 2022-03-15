#include "swap.h"

void swap(void *a, void *b, size_t sizeBat) {
    SWAP_BYT += sizeBat * 3;
    COUNT_SWAP++;

    swapMem(a, b, sizeBat);
}

void swapInt(void *a, void *b, size_t sizeBat) {
    int *arg1 = (int *) a;
    int *arg2 = (int *) b;

    int t = *arg1;
    *arg1 = *arg2;
    *arg2 = t;
}

void swapChar(void *a, void *b, size_t sizeBat) {
    char *arg1 = (char *) a;
    char *arg2 = (char *) b;

    char t = *arg1;
    *arg1 = *arg2;
    *arg2 = t;
}

// 8.83942857139961e-9 + 8.90420168074047e-11*sizeBat
// 7.18028983453146e-8 + 5.9806352210434e-11*sizeBat
void swapMem(void *a, void *b, size_t sizeBat) {
    static char t[MAX_SIZE];
    memcpy(t, a, sizeBat);
    memcpy(a, b, sizeBat);
    memcpy(b, t, sizeBat);
}

// 2.18414693849039e-8 + 1.23570708290034e-9*sizeBat
void swapForInt(void *a, void *b, size_t sizeBat) {
    size_t shift = sizeof(int);

    size_t countInt = sizeBat / shift;
    size_t countChar = sizeBat % shift;
    COUNT_COMPARE += countInt + countChar + 2;

    for (int i = 0; i < countInt; ++i) {
        SWAP_INT(a, b);

        a += shift;
        b += shift;
    }

    for (int i = 0; i < countChar; ++i) {
        SWAP_CHAR(a, b);

        a++;
        b++;
    }
}

size_t *getCountSwap() {
    static size_t countSwap = 0;
    return &countSwap;
}

size_t *getSwapByt() {
    static size_t countByt = 0;
    return &countByt;
}

