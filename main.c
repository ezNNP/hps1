#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "array_utils.h"
#include "quick_sort.h"
#include "test_utils.h"
#include "smooth_sort.h"

int main() {
    int *array = generate_random_array(ARRAY_LENGTH);
    int *quick_sorted = calloc(ARRAY_LENGTH, sizeof(int));
    memcpy(quick_sorted, array, sizeof(int) * ARRAY_LENGTH);
    qsort(quick_sorted, ARRAY_LENGTH, sizeof(int), compare);
    omp_set_num_threads(8);
    test_sorting_algorithm(array, quick_sorted, "Single-threaded quick sort", quick_sort);
    puts("");
    test_sorting_algorithm(array, quick_sorted, "Multi-threaded quick sort", quick_sort_parallel);
    puts("");
    test_sorting_algorithm(array, quick_sorted, "Single-threaded Smooth Sort", smooth_sort);
    puts("");
    test_sorting_algorithm(array, quick_sorted, "Multi-threaded Smooth Sort", smooth_sort_parallel);
    puts("");
    free(array);
    free(quick_sorted);
}
