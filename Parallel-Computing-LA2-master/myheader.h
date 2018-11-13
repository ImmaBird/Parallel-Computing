#ifndef MYHEADER_H_
#define MYHEADER_H_

double* mvp(double** mat, double* vec, int n);
void freeMat(double** mat, int n);
void assignMat(double** mat, int n, int val);
void assignVec(double* vec, int n, int val);
void printMatVec(double** mat, double* vec, double* ans, int n);
double* allocVec(int n);
double** allocMat(int n);
void printRow(double* row, int n);

#endif