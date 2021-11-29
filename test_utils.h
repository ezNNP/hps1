#ifndef L1_TEST_UTILS_H
#define L1_TEST_UTILS_H

#define ARRAY_LENGTH 5000000

double test_sorting_algorithm(int *original_array, int *verification_array, char *algorithm_name, int *(*algorithm)(int *, int));

#endif //L1_TEST_UTILS_H
