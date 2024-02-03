#include "matrix.h"
#include "time.h"
void print_menu()
{
    printf("\nМЕНЮ:\n\
          1 - стандартное умножение матриц;\n\
          2 - умножение матриц по алгоритму Винограда;\n\
          3 - умножение матриц по оптимизированному алгоритму Винограда;\n\
          4 - замерить время;\n\
          5 - замерить память;\n\
          0 - выход.\n\
        Выбор: \n");
}
int main()
{
    print_menu();
    int choice = 1;
    Matrix_t M1, M2, M;
    while (choice != 0)
    {
        printf("Ввести выбор из меню: \n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            input_from_user(&M1);
            input_from_user(&M2);
            if (M1.columns != M2.rows)
            {
                printf("Ввод неправильный\n");
                return -1;
            }
            allocate_matrix(&M, M1.rows, M2.columns);
            M = stand_mult(M, M1, M2);
            print_matrix(M);
            deallocate_matrix(&M1);
            deallocate_matrix(&M2);
            deallocate_matrix(&M);
        }
        else if (choice == 2)
        {
            input_from_user(&M1);
            input_from_user(&M2);
            if (M1.columns != M2.rows)
            {
                printf("Ввод неправильный\n");
                return -1;
            }
            allocate_matrix(&M, M1.rows, M2.columns);
            M = winograd_mul(M, M1, M2);
            print_matrix(M);
        }
        else if (choice == 3)
        {
            input_from_user(&M1);
            input_from_user(&M2);
            if (M1.columns != M2.rows)
            {
                printf("Ввод неправильный\n");
                return -1;
            }
            allocate_matrix(&M, M1.rows, M2.columns);
            M = optimized_winograd_mul(M, M1, M2);
            print_matrix(M);
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
            measure_time("stand_odd.txt", stand_mult);
            printf("Время замеров 2: \n");
            measure_time("wino_odd.txt", winograd_mul);
            printf("Время замеров 3: \n");
            measure_time("op_wino_odd.txt", optimized_winograd_mul);
        }
    }
    return 0;
}