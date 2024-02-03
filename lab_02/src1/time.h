#ifndef __TIME_H__
#define __TIME_H__

#include "matrix.h"
#include <time.h>
#define LEN_S  10
#define LEN_E  100

typedef Matrix_t (*alg_t)(Matrix_t, Matrix_t, Matrix_t);
void measure_time(char *filename, alg_t alg);
#endif