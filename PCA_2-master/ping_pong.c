#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int numranks, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int size = 125000000;

    double *buf = malloc(size * sizeof(double));

    double *send = malloc(size * sizeof(double));
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            send[i] = i % 10;
        }
    }

    int startTime = MPI_Wtime();
    if (rank == 0)
    {
        for (int i = 1; i < numranks; i++)
        {
            MPI_Send(send, size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Recv(buf, size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
        }
    }
    else
    {
        MPI_Recv(buf, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Send(buf, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    printf("Rank: %d, Elapsed Time: %f\n", rank, MPI_Wtime() - startTime);

    if (size <= 20)
    {
        for (int i = 0; i < numranks; i++)
        {
            if (rank == i)
            {
                printf("Rank: %d\n", rank);
                for (int j = 0; j < size; j++)
                {
                    printf("%.1f ", buf[j]);
                }
                printf("\n");
            }
        }
    }

    MPI_Finalize();
}
