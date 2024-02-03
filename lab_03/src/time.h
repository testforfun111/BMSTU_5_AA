#ifndef __TIME_H__
#define __TIME_H__

#include "sort.h"
#include <time.h>
#define LEN_S  10
#define LEN_E  1000

typedef void (*sort)(int *arr, int size);
void measure_time(char *filename, sort alg);
#endif