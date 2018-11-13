#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include "time.h"
#include "math.h"

double randomNum();

int main(int argc, char **argv)
{
    int numranks, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(time(NULL) + rank * 387);

    long trials = 100000000*atoi(argv[1]);
    long hits;

    long mystart = rank * ((trials / numranks) + 1);
    long myend = mystart + ((trials / numranks) + 1);
    if (myend > trials)
    {
        myend = trials;
    }

    for (int i = 0; i < numranks; i++)
    {
        if (rank == i)
        {
            //printf("Rank: %d Chunk: %ld\n", rank, myend - mystart);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    double start_time;

    if (rank == 0)
    {
        start_time = MPI_Wtime();
    }

    double x, y;
    hits = 0;

    for (long i = mystart; i < myend; i++)
    {
        x = randomNum();
        y = randomNum();
        if (x * x + y * y <= 1)
        {
            hits++;
        }
    }

    long total_hits;
    MPI_Reduce(&hits, &total_hits, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        double real_pi = acos(-1);
        double pi = 4 * (total_hits / (long double)trials);
        double error = 100 * (pi - real_pi) / real_pi;

        printf("%d,", numranks);
        printf("%.6f,", MPI_Wtime() - start_time);
        printf("%.12f,", pi);
        //printf("Real PI: %.12f\n", real_pi);
        printf("%.12f\n", error);
    }

    for (int i = 0; i < numranks; i++)
    {
        if (rank == i)
        {
            //printf("Hits: %ld\n", hits);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

double randomNum()
{
    //generates random number: [M,N]
    int M = -1;
    int N = 1;
    return (N - M) * (rand() / (double)RAND_MAX) + M;
}
