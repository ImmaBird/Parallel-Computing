//Wrong Result
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int numranks, rank, tag = 1, alpha, i;
    float beta;
    MPI_Status stats[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        if (numranks > 2)
            printf("Numranks=%d. Only 2 needed. Ignoring extra...\n", numranks);
        for (i = 0; i < 10; i++)
        {
            alpha = i * 10;
            MPI_Send(&alpha, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
            printf("Task %d sent = %d\n", rank, alpha);
        }
    }

    if (rank == 1)
    {
        for (i = 0; i < 10; i++)
        {
            // rank 0 sent an int so we need to receive an int
            int temp = 0;
            MPI_Recv(&temp, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &stats[i]);
            beta = (float)temp;
            printf("Task %d received = %f\n", rank, beta);
        }
    }

    MPI_Finalize();
}
