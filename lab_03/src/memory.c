#include "memory.h"

int *allocate_arr(int N)
{
    int *arr  = malloc(N * sizeof(N));
    return arr;
}

void deallocate_arr(int *arr)
{
    free(arr);
}
