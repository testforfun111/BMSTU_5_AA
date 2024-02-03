#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "memory.h"

int input_from_user(int **arr, int *size);
void print_arr(int *arr, int N);
void create_random_arr(int *arr, int size);
void create_random_arr_sorted_inc(int *arr, int size);
void create_random_arr_sorted_des(int *arr, int size);
void bubble_sort(int *arr, int size);
void bitonic_sort(int *arr, int size);
void radix_sort(int *arr, int n);
#endif 