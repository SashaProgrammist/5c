#ifndef INC_5C_GENERATINGFUNC_H
#define INC_5C_GENERATINGFUNC_H

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

// функция генерации
typedef struct GeneratingFunc {
    void (*generate )(int *array, size_t size); // указатель на функцию
    // генерации последоват.
    char name[64]; // имя генератора,
    // используемое при выводе
} GeneratingFunc;

void generateRandomArray(int *array, size_t size);

void generateOrderedArray(int *array, size_t size);

void generateOrderedBackwards(int *array, size_t size);

#endif //INC_5C_GENERATINGFUNC_H
