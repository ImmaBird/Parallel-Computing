#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

double norm(double *v, int n);
void freeMatrix(double **mat, int x);

int main(int argc, char **argv)
{

    //initialization
    double pi = acos(-1.0);
    double u0 = 0;
    double uL = 0;
    double alpha = 1;
    double L = 1;
    double tmax = 0.01;
    int nt = 10000; //for timing runs use 10000, for testing runs use 10
    int nx = 300; //for timing runs use 300, for testing runs use 10

    double dx = L / (nx - 1);
    double dt = tmax / (nt - 1);
    double r = alpha * dt / (dx * dx);
    if (r >= 0.5)
        printf("\n\nWARNING: Solution may be unstable. r=%f\n\n", r);
    double r2 = 1 - 2 * r;

    double **U = malloc(nx * sizeof(double *));
    double **A = malloc(nx * sizeof(double *));

    for (int i = 0; i < nx; i++)
    {
        U[i] = malloc(nt * sizeof(double));
        A[i] = malloc(nx * sizeof(double));
    }

    double *Ue = malloc(nx * sizeof(*Ue));
    double *vnorm = malloc(nx * sizeof(*vnorm));

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            A[i][j] = 0.0;
        }
    }

    for (int i = 0; i < nx; i++)
    {
        double temp = dx * (i);
        U[i][0] = sin(pi * temp / L);
        if (i == 0 || i == nx - 1)
        {
            A[i][i] = 1.0;
        }
        else
        {
            A[i][i] = 1 - 2 * r;
            A[i][i + 1] = r;
            A[i][i - 1] = r;
        }
    }

    //computation
    double startTime = omp_get_wtime();

#pragma omp parallel
    {
        
        for (int t = 1; t < nt; t++)
        {
            #pragma omp for
            for (int i = 0; i < nx; i++)
            {
                double temp = 0.0;
                for (int j = 0; j < nx; j++)
                {
                    temp += U[j][t - 1] * A[i][j];
                }
                U[i][t] = temp;
            }
        }

        #pragma omp barrier

        #pragma omp for
        for (int i = 0; i < nx; i++)
        {
            double temp = dx * (i);
            Ue[i] = sin(pi * temp / L) * exp(-tmax * alpha * (pi / L) * (pi / L));
            vnorm[i] = U[i][nt - 1] - Ue[i];
        }
    }

    double err = norm(vnorm, nx);

    double elapsedTime = omp_get_wtime() - startTime;
    printf("%.4f\n", elapsedTime);

    //printf("\nError ||approx-exact||: %f\n\n", err);

    //output
    //
    FILE *f = fopen("outputC.dat", "w");

    for (int i = 0; i < nx; i++)
    {
        fprintf(f, "%f    ", dx * i);
        for (int t = 0; t < nt; t++)
        {
            fprintf(f, "%f ", U[i][t]);
        }
        fprintf(f, "    %f\n", Ue[i]);
    }

    free(vnorm);
    free(Ue);
    freeMatrix(U, nx);
    freeMatrix(A, nx);

    fclose(f);
}

double norm(double *v, int n)
{

    double temp = 0;
    for (int i = 0; i < n; i++)
    {
        temp += v[i] * v[i];
    }
    return sqrt(temp);
}

void freeMatrix(double **mat, int x)
{
    for (int i = 0; i < x; i++)
    {
        free(mat[i]);
    }
    free(mat);
}
