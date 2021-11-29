#include "quick_sort.h"

void _qsort(int* array, int size) {
    int i = 0;
    int j = size - 1;
    int mid = array[size / 2];
    do {
        while (array[i] < mid) {
            i++;
        }
        while (array[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) _qsort(array, j + 1);
    if (i < size) _qsort(array + i, size - i);
}

void _qsort_parallel(int* array, int size) {
    int i = 0;
    int j = size - 1;
    int mid = array[size / 2];
    do {
        while (array[i] < mid) {
            i++;
        }
        while (array[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
#pragma omp task default(none) firstprivate(array, j) if(size > 1000)
    if (j > 0) _qsort_parallel(array, j + 1);
#pragma omp task default(none) shared(array, i, size) if(size > 1000)
    if (i < size) _qsort_parallel(array + i, size - i);
}

int* quick_sort_parallel(int *array, int length) {
    int* result = calloc(length, sizeof(int));
    for (int i = 0; i < length; i++) {
        result[i] = array[i];
    }
    omp_set_num_threads(8);
#pragma omp parallel default(none) shared(result, length)
    {
#pragma omp single nowait
        _qsort_parallel(result, length);
    }
    return result;
}

int* quick_sort(int* array, int length) {
    int* result = calloc(length, sizeof(int));
    for (int i = 0; i < length; i++) {
        result[i] = array[i];
    }
    _qsort(result, length);
    return result;
}

