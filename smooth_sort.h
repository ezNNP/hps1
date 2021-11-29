#ifndef L1_SMOOTH_SORT_H
#define L1_SMOOTH_SORT_H

typedef struct {
    int **array;
    long r;
    long q;
    long p;
    long b;
    long c;
    long r1;
    long b1;
    long c1;
} heap_info;

int *smooth_sort_parallel(int *array, int length);

int *smooth_sort(int *array, int length);

static void semi_trinkle(heap_info *info);

static void trinkle(heap_info *info);

static void sift(heap_info *info);

#endif //L1_SMOOTH_SORT_H
