#ifndef MYHEADER_H_
#define MYHEADER_H_

#define dot(ans, mat1, row, mat2, column, n) _Generic((mat1), \
              long double**: dotld, \
                  double**: dotd,  \
                    float**: dotf  \
)(ans, mat1, row, mat2, column, n)

void dotld(long double **ans, long double **mat1, int row, long double **mat2, int column, int n);
void dotd(double **ans, double **mat1, int row, double **mat2, int column, int n);
void dotf(float **ans, float **mat1, int row, float **mat2, int column, int n);

#define mvp(ans, mat1, mat2, column, n) _Generic((mat1), \
              long double**: mvpld, \
                  double**: mvpd,  \
                    float**: mvpf  \
)(ans, mat1, mat2, column, n)

void mvpld(long double **ans, long double **mat1, long double **mat2, int column, int n);
void mvpd(double **ans, double **mat1, double **mat2, int column, int n);
void mvpf(float **ans, float **mat1, float **mat2, int column, int n);

#define mmp(mat1, mat2, n) _Generic((mat1), \
              long double**: mmpld, \
                  double**: mmpd,  \
                    float**: mmpf  \
)(mat1, mat2, n)

long double **mmpld(long double **mat1, long double **mat2, int n);
double **mmpd(double **mat1, double **mat2, int n);
float **mmpf(float **mat1, float **mat2, int n);

// ------------------------------------------alloc stuff----------------------------------
long double **allocMatld(int n);
double **allocMatd(int n);
float **allocMatf(int n);

void assignMatld(long double **mat, int n, int val);
void assignMatd(double **mat, int n, int val);
void assignMatf(float **mat, int n, int val);

void freeMatld(long double **mat, int n);
void freeMatd(double **mat, int n);
void freeMatf(float **mat, int n);

long double *allocVecld(int n);
double *allocVecd(int n);
float *allocVecf(int n);

void assignVecld(long double *vec, int n, int val);
void assignVecd(double *vec, int n, int val);
void assignVecf(float *vec, int n, int val);

void printRow(double *row, int n);
void printMatMat(double **mat1, double **mat2, double **ans, int n);

#endif