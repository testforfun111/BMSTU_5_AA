#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdio.h>
#include <stdlib.h>

int *allocate_arr(int N);

void deallocate_arr(int *arr);

#endif