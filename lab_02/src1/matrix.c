#include "matrix.h"

int input_from_user(Matrix_t *M)
{
    printf("Ввести размер матрицы: \n");
    int rows, columns;
    if (scanf("%d%d", &rows, &columns) != 2)
        return -1;
    allocate_matrix(M, rows, columns);
    printf("Ввести элементы матрицы: ");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if (scanf("%d", &M->matrix[i][j]) != 1)
                return -1;
        }
    return 0;
}

void print_matrix(Matrix_t M)
{
    for (int i = 0; i < M.rows; i++)
    {
        for (int j = 0; j < M.columns; j++)
            printf("%d ", M.matrix[i][j]);
        printf("\n");
    }
}
void create_random_matrix(Matrix_t* M)
{
    srand(time(NULL));
    for (int i = 0; i < M->rows; i++)
        for (int j = 0; j < M->columns; j++)
            M->matrix[i][j] = rand() % 100;
}

Matrix_t stand_mult(Matrix_t M_result, Matrix_t M1, Matrix_t M2)
{
    if (M1.columns != M2.rows)
        return M_result;
    for (int i = 0; i < M1.rows; i++)
        for (int j = 0; j < M2.columns; j++)
            for (int k = 0; k < M1.columns; k++)
                M_result.matrix[i][j] += M1.matrix[i][k] * M2.matrix[k][j];
    return M_result;
}

Matrix_t winograd_mul(Matrix_t M_result, Matrix_t M1, Matrix_t M2)
{
    int n = M1.rows;
    int m = M2.columns;
    int p = M1.columns;

    int *row_factors = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p / 2; j++)
            row_factors[i] = row_factors[i] + M1.matrix[i][2 * j] * M1.matrix[i][2 * j + 1];
    
    int *column_factors = malloc(m * sizeof(int));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < p / 2; j++)
            column_factors[i] = column_factors[i] + M2.matrix[2 * j][i] * M2.matrix[2 * j + 1][i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            M_result.matrix[i][j] = M_result.matrix[i][j] - row_factors[i] - column_factors[j];
            for (int k = 0; k < p / 2; k++)
                M_result.matrix[i][j] = M_result.matrix[i][j] + \
                    (M1.matrix[i][2 * k + 1] + M2.matrix[2 * k][j]) * \
                     (M1.matrix[i][2 * k] + M2.matrix[2 * k + 1][j]);
        }
    if (p % 2 == 1)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                M_result.matrix[i][j] = M_result.matrix[i][j] + M1.matrix[i][p - 1] * M2.matrix[p - 1][j]; 
    }
    return M_result;
}

Matrix_t optimized_winograd_mul(Matrix_t M_result, Matrix_t M1, Matrix_t M2)
{
    int n = M1.rows;
    int m = M2.columns;
    int p = M1.columns;

    int d = p / 2;
    int *row_factors = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            row_factors[i] += M1.matrix[i][j << 1] * M1.matrix[i][(j << 1) + 1];
         
    int *column_factors = malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < d; j++)
            column_factors[i] += M2.matrix[j << 1][i] * M2.matrix[(j << 1) + 1][i];
            
    for (int i = 0; i < n; i++)
    {
        int row_factors_temp = -row_factors[i];
        for (int j = 0; j < m; j++)
        {   
            M_result.matrix[i][j] = row_factors_temp - column_factors[j];
            for (int k = 0; k < d; k++)
                M_result.matrix[i][j] += (M1.matrix[i][(k << 1) + 1] + M2.matrix[k << 1][j]) * \
                     (M1.matrix[i][k << 1] + M2.matrix[(k << 1) + 1][j]);
        }
    }

    if (p % 2 == 1)
    {
        for (int i = 0; i < n; i++)
        {
            // int temp_M1i = M1.matrix[i][p - 1];
            for (int j = 0; j < m; j++)
                M_result.matrix[i][j] += M1.matrix[i][p - 1] * M2.matrix[p - 1][j]; 
        }
    }
    return M_result;
}