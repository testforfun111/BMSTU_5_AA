#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdio.h>
#include <stdlib.h>
// #include "matrix.h"
struct Matrix{
    int **matrix;
    int rows;
    int columns;
};

typedef struct Matrix Matrix_t;

void allocate_matrix(Matrix_t *temp, int rows, int columns);

void deallocate_matrix(Matrix_t *M);
void reallocate_matrix(Matrix_t *temp, int rows, int columns);
#endif