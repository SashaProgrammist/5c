#include "test.h"

bool isOrdered(int *array, size_t size) {
    for (int i = 1; i < size; ++i)
        if (isLarge(array[i - 1], array[i]))
            return false;
    return true;
}

void check(void (*sortFunc)(int *, size_t),
           void (*generateFunc)(int *, size_t),
           size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[1000000];
    generateFunc(innerBuffer, size);

    printf("Run#%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер результатов
    double time;
    size_t countSwap, countCompare, swapBat;
    TEST({
             sortFunc(innerBuffer, size);
         }, time, countCompare, countSwap, swapBat)

    // результаты замера
    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK!\n"
               "\tTime: %.3f\n"
               "\tcountCompare: %zu\n"
               "\tcountSwap: %zu\n"
               "\tswapBat: %zu.\n",
               time, countCompare, countSwap, swapBat);

        // запись в файл
        char data[256];
        sprintf(data, "%zu;%.3f;%zu;%zu;%zu\n",
                size, time, countCompare, countSwap, swapBat);

        outputInFile(experimentName, data);
    } else {
        COUNT_ERROR++;

        printf("Wrong!\n");
        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);
        printf("\n");
    }
}

void outputArray_(int *array, size_t size) {
    for (int i = 0; i < size; ++i)
        printf("%d \n", array[i]);
}

void experiment_sortIndirect() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort, "bubbleSort"},
            {combSort, "combSort"},
            {shellSort, "shellSort"},
            {digitalSort, "digitalSort"},

            // вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray, "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray, "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("------------------------------\n");
        printf("Size: %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_sort",
                        sorts[i].name, generatingFuncs[j].name);

                check(sorts[i].sort,
                      generatingFuncs[j].generate,
                      size, filename);
            }
        }
        printf("\n");
    }
}

void checkSwapTime(void (*swapFunc)(void *, void *, size_t),
                   size_t size, char *experimentName){
    static char a[MAX_SIZE] = "a";
    static char b[MAX_SIZE] = "b";
    static bool is_aIna = true;
    static bool isChanges = RESOLUTION_STRAIGHT_TIME_TEST % 2;
    static size_t runCounter = 1;

    printf("Run#%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    double time;
    STRAIGHT_TIME_TEST({swapFunc(a, b, size);}, time)
    is_aIna = is_aIna ^ isChanges;

    if ((a[0] == 'a') == is_aIna){
        printf("OK!\tTime: %.20lf\n",
               time);

        char data[256];
        sprintf(data, "%zu,%.20lf\n",
                size, time);

        outputInFile(experimentName, data);
    } else {
        COUNT_ERROR++;

        printf("Wrong!\n");
    }
}

void experiment_swap(size_t shift, size_t maxSize) {
    SwapFunc swaps[] ={
            {swapForInt, "swapForInt"},
            {swapMem, "swapMem"}
    };
    const unsigned swapsN = ARRAY_SIZE(swaps);

    for (size_t size = shift; size <= maxSize; size += shift) {
        printf("------------------------------\n");
        printf("Size: %d\n", size);

        for (int i = 0; i < swapsN; ++i) {
            static char filename[128];
            sprintf(filename, "%s_timeSwap",
                    swaps[i].name);

            checkSwapTime(swaps[i].swap,
                          size, filename);
        }
    }
}

void outputInFile(char *fileName, char *data) {
    // запись в файл
    char filenamePath[256];
    sprintf(filenamePath, "././data/%s.csv", fileName);
    FILE *f = fopen(filenamePath, "a");

    if (f == NULL) {
        printf("FileOpenError %s", filenamePath);
        exit(1);
    }

    fprintf(f, data);

    fclose(f);
}

size_t *getCountError() {
    static size_t countError = 0;
    return &countError;
}


