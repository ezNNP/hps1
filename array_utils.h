#ifndef L1_ARRAY_UTILS_H
#define L1_ARRAY_UTILS_H

#include <malloc.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <limits.h>

int *generate_random_array(int length);

void print_array(int *array, int length);

int compare(const void *first_value, const void *second_value);

int *sort_parallel(int *array, int length, int *(*algorithm)(int *array, int length));

#endif //L1_ARRAY_UTILS_H
