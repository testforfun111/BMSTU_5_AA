#include "memory.h"

void allocate_matrix(Matrix_t *temp, int rows, int columns)
{
    int **matrix = malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++)
        matrix[i] = malloc(columns * sizeof(int));

    temp->matrix = matrix;
    temp->rows = rows;
    temp->columns = columns;
}

void reallocate_matrix(Matrix_t *temp, int rows, int columns)
{
    temp->rows = rows;
    temp->columns = columns;
    temp->matrix = realloc(temp->matrix, rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        temp->matrix[i] = realloc(temp->matrix[i], columns * sizeof(int));
}

void deallocate_matrix(Matrix_t *M)
{
    for (int i = 0; i < M->rows; i++)
    {
        free(M->matrix[i]);
    }
    free(M->matrix);
}