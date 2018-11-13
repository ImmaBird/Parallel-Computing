#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// resolution
int resx;
int resy;

// maximum iterations
int maxi = 255;

// mandelbrot window
double winxmin = -2;
double winxmax = 1;
double winymin = -1;
double winymax = 1;

int main(int argc, char *argv[])
{
    // get resolution from command line
    if (argc < 3)
    {
        printf("USAGE: command resx resy\n");
    }
    resx = atoi(argv[1]);
    resy = atoi(argv[2]);

    // print some information
    printf("Starting calculation...\n");
#pragma omp parallel
#pragma omp single
    printf("Number of threads: %d\n", omp_get_max_threads());

    // start calculation
    double startTime = omp_get_wtime();
    int count = 0;
    byte **values = allocMat(resx, resy);
#pragma omp parallel for schedule(dynamic) reduction(+:count)
    for (int x = 0; x < resx; x++)
    {
        for (int y = 0; y < resy; y++)
        {
            values[x][y] = isInMandel(getX0(x), getY0(y));

            // count the points in the set
            if (values[x][y] == 255)
            {
                count++;
            }
        }
    }

    // end calculation and print time
    double elapsedTime = omp_get_wtime() - startTime;
    printf("The program took %.4f seconds to run.\n", elapsedTime);
    double windowArea = (winxmax-winxmin)*(winymax-winymin);
    double percentMandel = (count+0.0)/(resx*resy);
    double mandelArea = percentMandel * windowArea;
    printf("Area of mandelbrot is %.2f", mandelArea);
    printData(values);

    freeMat(values, resx);

    return 0;
}

void printData(byte **values)
{
    FILE *f = fopen("./img.pgm", "w");
    int count = 0;
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", resx, resy);
    fprintf(f, "%d\n", maxi);
    for (int y = 0; y < resy; y++)
    {
        for (int x = 0; x < resx; x++)
        {
            count++;
            if (count == 13)
            {
                fprintf(f, "%d", values[x][y]);
                fprintf(f, "\n");
                count = 0;
            }
            else
            {
                fprintf(f, "%d ", values[x][y]);
            }
        }
    }
    fclose(f);
}

double getX0(int x)
{
    return (((x * 1.0) / resx) * (winxmax - winxmin)) + winxmin;
}

double getY0(int y)
{
    return (((y * 1.0) / resy) * (winymax - winymin)) + winymin;
}

byte isInMandel(double x0, double y0)
{
    double magz2 = 0;
    double x = 0;
    double y = 0;
    double xp = 0;
    double yp = 0;
    byte i = 0;
    for (; i < maxi && magz2 < 4; i++)
    {
        x = (xp * xp) - (yp * yp) + x0;
        y = (2 * xp * yp) + y0;
        magz2 = (xp * xp) + (yp * yp);
        xp = x;
        yp = y;
    }
    return i;
}

byte *allocVec(int n)
{
    byte *vec = malloc(n * sizeof(*vec));
    return vec;
}

byte **allocMat(int x, int y)
{
    byte **mat = malloc(x * sizeof(*mat));
#pragma omp parallel for
    for (int i = 0; i < x; i++)
    {
        mat[i] = allocVec(y);
    }
    return mat;
}

void freeMat(byte **mat, int x)
{
    for (int i = 0; i < x; i++)
    {
        free(mat[i]);
    }
    free(mat);
}