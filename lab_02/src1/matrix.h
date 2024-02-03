#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void create_random_matrix(Matrix_t* M);
Matrix_t stand_mult(Matrix_t M_result, Matrix_t M1, Matrix_t M2);
Matrix_t winograd_mul(Matrix_t M_result, Matrix_t M1, Matrix_t M2);
Matrix_t optimized_winograd_mul(Matrix_t M_result, Matrix_t M1, Matrix_t M2);
// Matrix_t strassen_mult(Matrix_t M_result, Matrix_t M1, Matrix_t M2);
int input_from_user(Matrix_t *M);
void print_matrix(Matrix_t M);
#endif 