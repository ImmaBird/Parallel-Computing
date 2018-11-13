#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "myheader.h"

void main(int argc, char *argv[]){
    if(argc < 2){
        printf("USAGE: command mat_size\n");
        return;
    }

    int n = atoi(argv[1]);

    // allocate
    double **mat = allocMat(n);
    double *vec = allocVec(n);
    
    // assign
    assignMat(mat, n, 2);
    assignVec(vec, n, 1);

    // compute
    double startTime = 0;
    double endTime = 0;
    double elapsedTime = 0;

    startTime = omp_get_wtime();
    double *ans = mvp(mat, vec, n);
    endTime = omp_get_wtime();
    elapsedTime = endTime - startTime;

    // print
    int numThreads = 0;
    #pragma omp parallel
    #pragma omp single
    numThreads = omp_get_num_threads();

    printf("Number of threads: %d\n", numThreads);
    printf("mvp ran in %.4f seconds.\n", elapsedTime);
    //printMatVec(mat, vec, ans, n);

    // free mem
    freeMat(mat, n);
    free(vec);
}


double* mvp(double** mat, double* vec, int n){
    double *ans = allocVec(n);
    int sum = 0;
    #pragma omp parallel for shared(ans, mat, vec) lastprivate(sum)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            sum += mat[i][j] * vec[i];
        }
        ans[i] = sum;
        sum = 0;
    }
    return ans;
}

void freeMat(double** mat, int n){
    for(int i = 0; i < n; i++){
        free(mat[i]);
    }
    free(mat);
}

void assignMat(double** mat, int n, int val){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int newVal = val - abs(i - j);
            if(newVal < 0){
                newVal = 0;
            }
            mat[i][j] = newVal;
        }
    }
}

void assignVec(double* vec, int n, int val){
    for(int i = 0; i < n; i++){
        vec[i] = val;
    }
}

void printMatVec(double** mat, double* vec, double* ans, int n){
    for(int i = 0; i < n; i++){
        printRow(mat[i], n);
        if(i != n/2){
            printf("    %.2f       ", vec[i]);
        }else{
            printf("    %.2f   =   ", vec[i]);
        }
        printf("%.2f\n", ans[i]);
    }
}

double* allocVec(int n){
    double *vec = malloc(n*sizeof(double));
    return vec;
}

double** allocMat(int n){
    double **mat = malloc(n*sizeof(*mat));
    for(int i = 0; i < n; i++){
        mat[i] = allocVec(n);
    }
    return mat;
}

void printRow(double* row, int n){
    for(int i = 0; i < n; i++){
        if(i != n-1){
            printf("%.2f  ", row[i]);
        }else{
            printf("%.2f", row[i]);
        }
    }
}