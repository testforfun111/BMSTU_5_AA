#include "sort.h"
#include "time.h"
void print_menu()
{
    printf("\nМЕНЮ:\n\
          1 - Битонная сортировка;\n\
          2 - Поразрядная сортировка;\n\
          3 - Сортировка пузырьком;\n\
          4 - Замерить время;\n\
          5 - Замерить память;\n\
          0 - Выход.\n\
        Выбор: \n");
}
int main()
{
    print_menu();
    int choice = 1;
    int *arr;
    int size;
    while (choice != 0)
    {
        printf("Ввести выбор из меню: \n");
        scanf("%d", &choice);
        if (choice == 3)
        {
            if (input_from_user(&arr, &size))
            {
                printf("Ввод неправильный\n");
                return -1;
            }
            bubble_sort(arr, size);
            print_arr(arr, size);
            deallocate_arr(arr);
        }
        else if (choice == 1)
        {
            if (input_from_user(&arr, &size))
            {
                printf("Ввод неправильный\n");
                return -1;
            }
            // int n = (int) log(size);
            // int new_size = (int) pow(2, n);
            // if (new_size < size)
            //     new_size = (int) pow(2, n + 1);
            
            // int *arr_new = allocate_arr(new_size);
            bitonic_sort(arr, size);
            print_arr(arr, size);
            deallocate_arr(arr);
        }
        else if (choice == 2)
        {
            if (input_from_user(&arr, &size))
            {
                printf("Ввод неправильный\n");
                return -1;
            }
            // int n = (int) log(size);
            // int new_size = (int) pow(2, n);
            // if (new_size < size)
            //     new_size = (int) pow(2, n + 1);
            
            // int *arr_new = allocate_arr(new_size);
            radix_sort(arr, size);
            print_arr(arr, size);
            deallocate_arr(arr);
        }
        else if (choice == 4)
        {
            // printf("Время замеров 1: \n");
            // measure_time("stand.txt", stand_mult);
            // printf("Время замеров 2: \n");
            // measure_time("wino.txt", winograd_mul);
            // printf("Время замеров 3: \n");
            // measure_time("op_wino.txt", optimized_winograd_mul);
            // system("python3 ./grap_result.py");
            printf("Время замеров 1: \n");
            measure_time("bitonic.txt", bitonic_sort);
            printf("Время замеров 2: \n");
            measure_time("radix.txt", radix_sort);
            printf("Время замеров 3: \n");
            measure_time("bubble.txt", bubble_sort);
        }
    }
    return 0;
}