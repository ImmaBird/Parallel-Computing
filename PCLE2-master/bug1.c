//Hangs
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int numranks, rank, dest, tag, source, rc, count;
    char inmsg, outmsg = 'x';
    MPI_Status Stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numranks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Task %d starting...\n", rank);

    // set tag to 0, tag must be the same for the send and receive
    tag = 0;

    if (rank == 0)
    {
        if (numranks > 2)
            printf("Numranks=%d. Only 2 needed. Ignoring extra...\n", numranks);
        dest = rank + 1;
        source = dest;
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        printf("Sent to task %d...\n", dest);
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        printf("Received from task %d...\n", source);
    }
    else if (rank == 1)
    {
        dest = rank - 1;
        source = dest;
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        printf("Received from task %d...\n", source);
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        printf("Sent to task %d...\n", dest);
    }

    if (rank < 2)
    {
        rc = MPI_Get_count(&Stat, MPI_CHAR, &count);
        printf("Task %d: Received %d char(s) from rank %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
    }

    MPI_Finalize();
}
