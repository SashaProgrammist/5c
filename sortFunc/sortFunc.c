#include "sortFunc.h"

void selectionSort(int *array, size_t size) {
    for (size_t i = 0; isLess(i, size); ++i) {
        size_t minIndex = i;

        for (size_t j = i + 1; isLess(j, size); ++j)
            if (isLarge(array[minIndex],
                        array[j]))
                minIndex = j;

        if (!isEqual(minIndex, i))
            SWAP(array + i,
                 array + minIndex);
    }
}

void insertionShiftSort(int *array, size_t size,
                        int shift) {
    for (int i = shift; isLess(i, size); i++) {
        SWAP_BYT += sizeof(int);
        int current = array[i];

        int j = i;
        int k = i - shift;
        while (isEqualOrLarge(j, shift) &&
               isLarge(array[k],
                       current)) {
            array[j] = array[k];
            SWAP_BYT += sizeof(int);
            j -= shift;
            k -= shift;
        }

        SWAP_BYT += sizeof(int);
        array[j] = current;
    }
}

void insertionSort(int *array, size_t size) {
    insertionShiftSort(array, size, 1);
}

void comb(int *current, int *previous,
          size_t count) {
    for (size_t i = 0; isLess(i, count); ++i) {
        if (isLarge(*previous, *current))
            SWAP(previous, current);

        current++;
        previous++;
    }
}

void bubbleSort(int *array, size_t size) {
    for (size_t i = 0; isLess(i, size); ++i) {
        size_t count = size - i - 1;
        int *current = array + 1;
        int *previous = array;

        comb(current, previous, count);
    }
}

void combSort(int *array, size_t size) {
    static const double coefficient =
            1.2473309501039786528764352624421007931232452392578125;

    size_t shift = size - 1;
    while (isLarge(shift, 10)) {
        size_t count = size - shift;
        int *current = array + shift;
        int *previous = array;

        comb(current, previous, count);

        shift = shift / coefficient;
    }

    insertionSort(array, size);
}

int *getShellCoefficients() {
    static int coefficients[] = {
            1, 5, 19, 41,
            109, 209, 505, 929,
            2161, 3905, 8929,
            16001, 36289, 64769,
            146305, 260609,
            587521, 1045505,
            2354689, 4188161,
            9427969,
    };

    return coefficients;
}

void shellSort(int *array, size_t size) {
    int *coefficients = getShellCoefficients();
    size_t indexEnd = 0;

    while (isLess(coefficients[indexEnd] * 3, size))
        indexEnd++;

    for (size_t i = indexEnd; isLarge(i + 1, 0); --i)
        insertionShiftSort(array, size,
                           coefficients[i]);
}

int bufferDigitalSort[100000];

void digitalSortOneByt(int *array, size_t size, int NByt) {
    static int countDigits = 1 << 8;
    static int numbersDigits[1 << 8];
    static int mask = (1 << 8) - 1;

    for (int i = 0; isLess(i, countDigits); ++i)
        numbersDigits[i] = 0;

    int shift = 8 * NByt;
    for (int i = 0; isLess(i, size); ++i) {
        int digit = (array[i] >> shift) & mask;
        numbersDigits[digit]++;
    }

    for (int i = 1; isLess(i, countDigits); ++i)
        numbersDigits[i] += numbersDigits[i - 1];

    for (int i = size - 1; isEqualOrLarge(i, 0); --i) {
        int digit = (array[i] >> shift) & mask;
        numbersDigits[digit]--;
        bufferDigitalSort[numbersDigits[digit]] = array[i];
    }

    memcpy(array, bufferDigitalSort, size * sizeof(int));
}

void digitalNegativeSort(int *array, size_t size) {
    int indexFirstNegative = size;
    while (isEqualOrLarge(indexFirstNegative, 0) &&
           isLess(array[indexFirstNegative - 1], 0))
        indexFirstNegative--;

    if (!isEqual(indexFirstNegative, size) &&
        !isEqual(indexFirstNegative, -1)){
        int countNegative = size - indexFirstNegative;

        memcpy(bufferDigitalSort,
               array + indexFirstNegative,
               countNegative * sizeof(int));

        memcpy(bufferDigitalSort + countNegative,
               array,
               indexFirstNegative * sizeof(int));

        memcpy(array, bufferDigitalSort, size * sizeof(int));
    }
}

void digitalSort(int *array, size_t size) {
    for (int i = 0; isLess(i, sizeof(int)); ++i)
        digitalSortOneByt(array, size, i);

    digitalNegativeSort(array, size);
}
