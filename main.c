#include "test/test.h"

#define N 5

int main() {
//    experiment_sortIndirect();

    int a[N];
    generateOrderedBackwards(a, N);
    outputArray_(a, N);
    printf("\n");
    combSort(a, N);
    outputArray_(a, N);
    printf("\n %d \n", isOrdered(a, N));
//
//    clock_t start_time = clock();
//    for (int i = 0; i < 1000; ++i) {
//        generateRandomArray(a, N);
//        combSort(a, N);
//    }
//    clock_t end_time = clock();
//    clock_t sort_time = end_time - start_time;
//    double time = (double) sort_time / CLOCKS_PER_SEC;
//    printf("%lf %lf", time, time / 1000);

    return COUNT_ERROR;
}
