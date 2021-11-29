#ifndef L1_QUICK_SORT_H
#define L1_QUICK_SORT_H

#include <stdlib.h>
#include <omp.h>

int *quick_sort_parallel(int *array, int length);

int *quick_sort(int *array, int length);

#endif //L1_QUICK_SORT_H
