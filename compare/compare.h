#ifndef INC_5C_COMPARE_H
#define INC_5C_COMPARE_H

#include <stdlib.h>
#include <stdbool.h>

#define COUNT_COMPARE (*getCountCompare())
size_t *getCountCompare();

int compare_int(int a, int b);

int compare_size_t(size_t a, size_t b);

bool isLess(int a, int b);

bool isLessOrEqual(int a, int b);

bool isEqual(int a, int b);

bool isEqualOrLarge(int a, int b);

bool isLarge(int a, int b);

#endif //INC_5C_COMPARE_H
