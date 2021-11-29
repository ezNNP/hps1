#include <malloc.h>
#include <string.h>
#include "smooth_sort.h"
#include "array_utils.h"

#define UP(IA, IB) temp = IA; (IA) += (IB) + 1; (IB) = temp;
#define DOWN(IA, IB) temp = IB; (IB) = (IA) - (IB) - 1; (IA) = temp;

int *smooth_sort_parallel(int *array, int length) {
    return sort_parallel(array, length, smooth_sort);
}

int *smooth_sort(int *array, int length) {
    int *result = malloc(length * sizeof(int));
    memcpy(result, array, length * sizeof(int));
    heap_info *info = malloc(sizeof(heap_info));
    long temp;
    info->array = &result;
    info->q = 1;
    info->r = 0;
    info->p = 1;
    info->b = 1;
    info->c = 1;
    while (info->q < length) {
        info->r1 = info->r;
        if ((info->p & 7) == 3) {
            info->b1 = info->b;
            info->c1 = info->c;
            sift(info);
            info->p = (info->p + 1) >> 2;
            UP(info->b, info->c);
            UP(info->b, info->c);
        } else if ((info->p & 3) == 1) {
            if (info->q + info->c < length) {
                info->b1 = info->b;
                info->c1 = info->c;
                sift(info);
            } else {
                trinkle(info);
            }
            DOWN(info->b, info->c);
            info->p <<= 1;
            while (info->b > 1) {
                DOWN(info->b, info->c);
                info->p <<= 1;
            }
            info->p++;
        }
        info->q++;
        info->r++;
    }
    info->r1 = info->r;
    trinkle(info);
    while (info->q > 1) {
        --info->q;
        if (info->b == 1) {
            info->r--;
            info->p--;
            while ((info->p & 1) == 0) {
                info->p >>= 1;
                UP(info->b, info->c);
            }
        } else {
            if (info->b >= 3) {
                info->p--;
                info->r = info->r - info->b + info->c;
                if (info->p > 0)
                    semi_trinkle(info);
                DOWN(info->b, info->c);
                info->p = (info->p << 1) + 1;
                info->r = info->r + info->c;
                semi_trinkle(info);
                DOWN(info->b, info->c);
                info->p = (info->p << 1) + 1;
            }
        }
    }
    free(info);
    return result;
}

static void sift(heap_info *info) {
    long r0, r2, temp;
    int t;
    r0 = info->r1;
    t = (*info->array)[r0];
    while (info->b1 >= 3) {
        r2 = info->r1 - info->b1 + info->c1;
        if ((*info->array)[info->r1 - 1] > (*info->array)[r2]) {
            r2 = info->r1 - 1;
            DOWN(info->b1, info->c1);
        }
        if ((*info->array)[r2] <= t) {
            info->b1 = 1;
        } else {
            (*info->array)[info->r1] = (*info->array)[r2];
            info->r1 = r2;
            DOWN(info->b1, info->c1);
        }
    }
    if (info->r1 - r0)
        (*info->array)[info->r1] = t;
}

static void trinkle(heap_info *info) {
    long p1, r2, r3, r0, temp;
    p1 = info->p;
    info->b1 = info->b;
    info->c1 = info->c;
    r0 = info->r1;
    int t = (*info->array)[r0];
    while (p1 > 0) {
        while ((p1 & 1) == 0) {
            p1 >>= 1;
            UP(info->b1, info->c1)
        }
        r3 = info->r1 - info->b1;
        if ((p1 == 1) || (*info->array)[r3] <= t) {
            p1 = 0;
        } else {
            --p1;
            if (info->b1 == 1) {
                (*info->array)[info->r1] = (*info->array)[r3];
                info->r1 = r3;
            } else {
                if (info->b1 >= 3) {
                    r2 = info->r1 - info->b1 + info->c1;
                    if ((*info->array)[info->r1 - 1] > (*info->array)[r2]) {
                        r2 = info->r1 - 1;
                        DOWN(info->b1, info->c1);
                        p1 <<= 1;
                    }
                    if ((*info->array)[r2] <= (*info->array)[r3]) {
                        (*info->array)[info->r1] = (*info->array)[r3];
                        info->r1 = r3;
                    } else {
                        (*info->array)[info->r1] = (*info->array)[r2];
                        info->r1 = r2;
                        DOWN(info->b1, info->c1);
                        p1 = 0;
                    }
                }
            }
        }
    }
    if (r0 - info->r1)
        (*info->array)[info->r1] = t;
    sift(info);
}

static void semi_trinkle(heap_info *info) {
    int temp;
    info->r1 = info->r - info->c;
    if ((*info->array)[info->r1] > (*info->array)[info->r]) {
        temp = (*info->array)[info->r];
        (*info->array)[info->r] = (*info->array)[info->r1];
        (*info->array)[info->r1] = temp;
        trinkle(info);
    }
}