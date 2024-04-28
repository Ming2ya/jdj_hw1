#include "algebra.h"
#include <stdio.h>
#include <math.h>
int i,j;
Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if ( a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int i, j;
        Matrix m=create_matrix(a.rows, a.rows);
        for ( i = 0; i < a.rows; i++)
        {
            for ( j = 0; j < a.rows; j++)
            {
                m.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return m;
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if ( a.rows != b.rows || a.cols != b.cols)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int i, j;
        Matrix m=create_matrix(a.rows, a.rows);
        for (i = 0; i < a.rows; i++)
        {
            for (j = 0; j < a.rows; j++)
            {
                m.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return m;
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else 
    {
        int i, j, k;
        Matrix m=create_matrix(a.rows, b.cols);
        for (i = 0; i < a.rows; i++)
        {
            for (j = 0; j < b.cols; j++){
                double sum = 0.0;
                for (k = 0; k < a.cols; k++)
                {
                    sum += a.data[i][k] * b.data[k][j];
                }
                m.data[i][j] = sum;
            }
        }
        return m;
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix m=create_matrix(a.rows, a.cols);
    int i, j;
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            m.data[i][j] = a.data[i][j] * k;
        }
    }
    return m;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix m=create_matrix(a.cols, a.rows);
    int i, j;
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            m.data[j][i] = a.data[i][j];
        }
    }
    return m;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else
    {
        if (a.rows == 1)
        {
            return a.data[0][0];
        }
        else
        {
            int i, j, k;
            double sum = 0.0;
            for (i = 0; i < a.cols; i++)
            {
                Matrix b = create_matrix(a.rows-1, a.cols-1);
                for (j = 1; j < a.rows; j++){
                    int flag = 0;
                    for (k = 0; k < a.cols; k++)
                    {
                        if (k == i)
                        {
                            flag = 1;
                            continue;
                        }
                        else 
                        {
                            b.data[j - 1][k - flag] = a.data[j][k];
                        }
                    }
                }
                sum += ((i % 2) ? -1 : 1) * a.data[0][i] * det_matrix(b);
            }
            return sum;
        }
    }
}
Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    int r;
    if (a.cols >= a.rows)
    {
        r = a.rows;
    }
    else
    {
        r = a.cols;
        a = transpose_matrix(a);
    }
    int i, j, k;
    for (int i = 0; i < a.rows; i++)
    {
        if (a.data[i][i] != 0)
        {
            for (j = i + 1; j < a.rows; j++)
            {
                double t = a.data[j][i] / a.data[i][i];
                for (k = i; k < a.cols; k++)
                {
                    a.data[j][k] -= a.data[i][k];
                }
            }
        }
        else{
            int flag = 0;
            for (j = i + 1; j < a.rows; j++)
            {
                if (a.data[j][i] != 0)
                {
                    flag = 1;
                    for (k = i; k < a.cols; k++)
                    {
                        double temp;
                        temp = a.data[i][k]; 
                        a.data[i][k] = a.data[j][k];
                        a.data[j][k] = temp;
                    }
                    break;
                }
            }
            if (flag != 0)
            {
                for (j = i + 1; j < a.rows; j++)
                {
                    double t = a.data[j][i] / a.data[i][i];
                    for (k = i; k < a.cols; k++){
                        a.data[j][k] -= a.data[i][k];
                    }
                }
            }
            else
            {
                r-=1;
            }
        }
    }
    return r;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else 
    {
        int k;
        double tr=0.0;
        for (k = 0; k < a.rows; k++)
        {
            tr+=a.data[k][k];
        }
        return tr;
    }
    return 0;
}

void print_matrix(Matrix a)
{
    int i, j;
    for (i = 0; i < a.rows; i++)
    {
        for (j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}