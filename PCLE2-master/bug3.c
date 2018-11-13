//Hangs
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int numranks, rank, len, buffer, root, count;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(hostname, &len);

    printf("Task %d on %s starting...\n", rank, hostname);
    root = 0;
    // count needs to be 1 because we are sending 1 int
    count = 1;
    buffer = 0;
    if (rank == root)
    {
        buffer = 23;
        printf("Root: Number of MPI tasks is: %d\n", numranks);
    }

    MPI_Bcast(&buffer, count, MPI_INT, root, MPI_COMM_WORLD);

    printf("Rank: %d, Buffer: %d", rank, buffer);

    MPI_Finalize();
}
