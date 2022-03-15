#ifndef INC_5C_SORTFUNC_H
#define INC_5C_SORTFUNC_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../compare/compare.h"
#include "../swap/swap.h"

// функция сортировки
typedef struct SortFunc {
    void (*sort )(int *array, size_t size); // указатель на функцию
    //                                         сортировки
    char name[64]; // имя сортировки,
    //                используемое при выводе
} SortFunc;

void selectionSort(int *array, size_t size);

void insertionSort(int *array, size_t size);

void bubbleSort(int *array, size_t size);

void combSort(int *array, size_t size);

void shellSort(int *array, size_t size);

void digitalSort(int *array, size_t size);

#endif //INC_5C_SORTFUNC_H
