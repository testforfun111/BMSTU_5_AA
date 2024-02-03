#include "time.h"
#include <math.h>

int temp[9] = {2, 4, 8, 16, 32, 64, 128, 256, 512};

void copy_arr(int *arr1, int *arr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr2[i] = arr1[i];
    }
}
void measure_time(char *filename, sort alg)
{
    float seconds;
    int *arr, *arr2;
    FILE *f = fopen(filename, "w");
    // for (int len = LEN_S; len < LEN_E; len += 50)
    // {
    //     arr = allocate_arr(len);
    //     clock_t start = clock();
    //     for (int i = 0; i < 10; i++)
    //         alg(arr, len);
    //     clock_t end = clock();
    //     deallocate_arr(arr);
    //     seconds = (float) (end - start) / CLOCKS_PER_SEC * 1000;
    //     printf("%f\n", seconds);
    //     fprintf(f, "%d %lf ", len, seconds);
    // }
    for (int i = 0; i < 9; i++)
    {
        arr = allocate_arr(temp[i]);
        arr2 = allocate_arr(temp[i]);

        // create_random_arr(arr, temp[i]);
        create_random_arr_sorted_inc(arr, temp[i]);
        // create_random_arr_sorted_des(arr, temp[i]);

        copy_arr(arr, arr2, temp[i]);
        clock_t start = clock();
        for (int j = 0; j < 1; j++)
            alg(arr2, temp[i]);
        clock_t end = clock();
        deallocate_arr(arr);
        deallocate_arr(arr2);
        seconds = (float) (end - start) / CLOCKS_PER_SEC * 1000;
        printf("%f\n", seconds);
        fprintf(f, "%d %lf ", temp[i], seconds);
        // fprintf(f, "%lf\n", seconds);
    }
    fclose(f);
}
