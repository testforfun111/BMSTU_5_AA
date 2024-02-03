#include "sort.h"

int input_from_user(int **arr, int *size)
{
    printf("Ввести размер массивы: \n");
    if (scanf("%d", size) != 1)
        return -1;
    *arr = allocate_arr(*size);

    printf("Ввести элементы массивы: ");
    for (int j = 0; j < *size; j++)
    {
        if (scanf("%d", *arr + j) != 1)
            return -1;
    }
    return 0;
}

void print_arr(int *arr, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
}

void create_random_arr(int *arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 1000;
}

void create_random_arr_sorted_inc(int *arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        int temp = rand() % 1000;

        if (i > 0 && temp >= arr[i - 1])
            arr[i] = temp;
        else
            arr[i] = rand() % 100;
    }
}

void create_random_arr_sorted_des(int *arr, int size)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        int temp = rand() % 1000;

        if (i > 0 && temp <= arr[i - 1])
            arr[i] = temp;
        else
            arr[i] = rand() % 100;
    }
}

void swap(int *A, int *B)
{
    int c = *A;
    *A = *B;
    *B = c;
}

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + j + 1);
}

void compAndSwap(int *arr, int i, int j, int dir)
{
    if (dir==(arr[i]>arr[j]))
        swap(arr + i, arr + j);
}

void bitonicMerge(int *arr, int low, int cnt, int dir)
{
    if (cnt>1)
    {
        int k = cnt/2;
        for (int i=low; i<low+k; i++)
            compAndSwap(arr, i, i+k, dir);
        bitonicMerge(arr, low, k, dir);
        bitonicMerge(arr, low+k, k, dir);
    }
}
 
void bitonicSort(int *arr,int low, int cnt, int dir)
{
    if (cnt>1)
    {
        int k = cnt/2;
 
        bitonicSort(arr, low, k, 1);
 
        bitonicSort(arr, low+k, k, 0);
 
        bitonicMerge(arr, low, cnt, dir);
    }
}

void bitonic_sort(int *arr, int size)
{
    bitonicSort(arr, 0, size, 1);
}

int getMax(int *arr, int n)
{
    int mx = *arr;
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
void countSort(int *arr, int n, int exp)
{
    int *output = allocate_arr(n);
    int i, count[10] = { 0 };
 
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    deallocate_arr(output);
}

void radix_sort(int *arr, int n)
{
    int m = getMax(arr, n);
 
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}