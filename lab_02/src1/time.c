#include "time.h"
#include <math.h>

void measure_time(char *filename, alg_t alg)
{
    Matrix_t C, A, B;
    float seconds;
    FILE *f = fopen(filename, "w");
    for (int len = LEN_S + 1; len < LEN_E + 2; len += 10)
    {
        allocate_matrix(&A, len, len);
        allocate_matrix(&B, len, len);
        allocate_matrix(&C, len, len);
        create_random_matrix(&B);
        create_random_matrix(&C);
        clock_t start = clock();
        for (int i = 0; i < 10; i++)
            alg(C, A, B);
        clock_t end = clock();
        deallocate_matrix(&B);
        deallocate_matrix(&C);
        deallocate_matrix(&A);
        seconds = (float) (end - start) / CLOCKS_PER_SEC * 1000;
        printf("%f\n", seconds);
        fprintf(f, "%d %lf ", len, seconds);
    }
    fclose(f);
}
