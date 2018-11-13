#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "myheader.h"

void main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("USAGE: command mat_size\n");
        return;
    }

    int n = atoi(argv[1]);
    {
        // --------------------------------------------------------------------------------long double
        // allocate
        long double **mat1 = allocMatld(n);
        long double **mat2 = allocMatld(n);

        // assign
        assignMatld(mat1, n, n / 2);
        assignMatld(mat2, n, n / 2);

        // compute
        double startTime = 0;
        double endTime = 0;
        double elapsedTime = 0;

        startTime = omp_get_wtime();
        long double **ans = mmp(mat1, mat2, n);
        endTime = omp_get_wtime();
        elapsedTime = endTime - startTime;

        // print
        int numThreads = 0;
#pragma omp parallel
#pragma omp single
        numThreads = omp_get_num_threads();

        printf("Number of threads: %d\n", numThreads);
        printf("long double mmp ran in %.4f seconds.\n", elapsedTime);
        //printMatMat(mat1, mat2, ans, n);

        // free mem
        freeMatld(mat1, n);
        freeMatld(mat2, n);
        freeMatld(ans, n);
    }
    // ------------------------------------------------------------------------------------double
    {
        // allocate
        double **mat1 = allocMatd(n);
        double **mat2 = allocMatd(n);

        // assign
        assignMatd(mat1, n, n / 2);
        assignMatd(mat2, n, n / 2);

        // compute
        double startTime = 0;
        double endTime = 0;
        double elapsedTime = 0;

        startTime = omp_get_wtime();
        double **ans = mmp(mat1, mat2, n);
        endTime = omp_get_wtime();
        elapsedTime = endTime - startTime;

        // print
        int numThreads = 0;
#pragma omp parallel
#pragma omp single
        numThreads = omp_get_num_threads();

        printf("Number of threads: %d\n", numThreads);
        printf("double mmp ran in %.4f seconds.\n", elapsedTime);
        //printMatMat(mat1, mat2, ans, n);

        // free mem
        freeMatd(mat1, n);
        freeMatd(mat2, n);
        freeMatd(ans, n);
    }
    // ------------------------------------------------------------------------------------int
    {
        // allocate
        float **mat1 = allocMatf(n);
        float **mat2 = allocMatf(n);

        // assign
        assignMatf(mat1, n, n / 2);
        assignMatf(mat2, n, n / 2);

        // compute
        double startTime = 0;
        double endTime = 0;
        double elapsedTime = 0;

        startTime = omp_get_wtime();
        float **ans = mmp(mat1, mat2, n);
        endTime = omp_get_wtime();
        elapsedTime = endTime - startTime;

        // print
        int numThreads = 0;
#pragma omp parallel
#pragma omp single
        numThreads = omp_get_num_threads();

        printf("Number of threads: %d\n", numThreads);
        printf("int mmp ran in %.4f seconds.\n", elapsedTime);
        //printMatMat(mat1, mat2, ans, n);

        // free mem
        freeMatf(mat1, n);
        freeMatf(mat2, n);
        freeMatf(ans, n);
    }
}

void printRow(double *row, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
        {
            printf("%.2f ", row[i]);
        }
        else
        {
            printf("%.2f", row[i]);
        }
    }
}

void printMatMat(double **mat1, double **mat2, double **ans, int n)
{
    for (int i = 0; i < n; i++)
    {
        printRow(mat1[i], n);
        printf("     ");
        printRow(mat2[i], n);
        if (i != n / 2)
        {
            printf("       ");
        }
        else
        {
            printf("   =   ");
        }
        printRow(ans[i], n);
        printf("\n");
    }
}

// ----------------------------------------------------long double-------------------------------------------------------------
// A matrix is represented as an array of rows where a row is another array
// row dot column
void dotld(long double **ans, long double **mat1, int row, long double **mat2, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        ans[row][column] += mat1[row][i] * mat2[i][column];
    }
}

// iterates over rows
// rows dot column
void mvpld(long double **ans, long double **mat1, long double **mat2, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        dotld(ans, mat1, i, mat2, column, n);
    }
}

// iterates over columns
// rows dot columns
long double **mmpld(long double **mat1, long double **mat2, int n)
{
    long double **ans = allocMatld(n);
    assignMatld(ans, n, 0);
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        mvpld(ans, mat1, mat2, i, n);
    }
    return ans;
}

long double *allocVecld(int n)
{
    long double *vec = malloc(n * sizeof(long double));
    return vec;
}

long double **allocMatld(int n)
{
    long double **mat = malloc(n * sizeof(*mat));
    for (int i = 0; i < n; i++)
    {
        mat[i] = allocVecld(n);
    }
    return mat;
}

void assignMatld(long double **mat, int n, int val)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int newVal = val - abs(i - j);
            if (newVal < 0)
            {
                newVal = 0;
            }
            mat[i][j] = newVal;
        }
    }
}

void freeMatld(long double **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

// ----------------------------------------------------double-------------------------------------------------------------
// A matrix is represented as an array of rows where a row is another array
// row dot column
void dotd(double **ans, double **mat1, int row, double **mat2, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        ans[row][column] += mat1[row][i] * mat2[column][i]; // fliped
        // ans[row][column] += mat1[row][i] * mat2[i][column]; // original
    }
}

// iterates over rows
// rows dot column
void mvpd(double **ans, double **mat1, double **mat2, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        dotd(ans, mat1, i, mat2, column, n);
    }
}

// iterates over columns
// rows dot columns
double **mmpd(double **mat1, double **mat2, int n)
{
    double **ans = allocMatd(n);
    assignMatd(ans, n, 0);
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        mvpd(ans, mat1, mat2, i, n);
    }
    return ans;
}

double *allocVecd(int n)
{
    double *vec = malloc(n * sizeof(double));
    return vec;
}

void assignVecd(double *vec, int n, int val)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = val;
    }
}

double **allocMatd(int n)
{
    double **mat = malloc(n * sizeof(*mat));
    for (int i = 0; i < n; i++)
    {
        mat[i] = allocVecd(n);
    }
    return mat;
}

void assignMatd(double **mat, int n, int val)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int newVal = val - abs(i - j);
            if (newVal < 0)
            {
                newVal = 0;
            }
            mat[i][j] = newVal;
        }
    }
}

void freeMatd(double **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

// ----------------------------------------------------float-------------------------------------------------------------
// A matrix is represented as an array of rows where a row is another array
// row dot column
void dotf(float **ans, float **mat1, int row, float **mat2, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        ans[row][column] += mat1[row][i] * mat2[i][column];
    }
}

// iterates over rows
// rows dot column
void mvpf(float **ans, float **mat1, float **mat2, int column, int n)
{
    for (int i = 0; i < n; i++)
    {
        dotf(ans, mat1, i, mat2, column, n);
    }
}

// iterates over columns
// rows dot columns
float **mmpf(float **mat1, float **mat2, int n)
{
    float **ans = allocMatf(n);
    assignMatf(ans, n, 0);
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        mvpf(ans, mat1, mat2, i, n);
    }
    return ans;
}

float *allocVecf(int n)
{
    float *vec = malloc(n * sizeof(float));
    return vec;
}

void assignVecf(float *vec, int n, int val)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = val;
    }
}

float **allocMatf(int n)
{
    float **mat = malloc(n * sizeof(*mat));
    for (int i = 0; i < n; i++)
    {
        mat[i] = allocVecf(n);
    }
    return mat;
}

void assignMatf(float **mat, int n, int val)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            float newVal = val - abs(i - j);
            if (newVal < 0)
            {
                newVal = 0;
            }
            mat[i][j] = newVal;
        }
    }
}

void freeMatf(float **mat, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
}