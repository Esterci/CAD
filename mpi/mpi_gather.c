#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int myrank, size, recvbufflen = 0;
    int *recvbuffer;
    int sendbuffer[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < 2; i++)
        sendbuffer[i] = myrank*2 + i;
    if (myrank == 0)
    {
        recvbufflen = 2 * size;
        recvbuffer = (int *)malloc(recvbufflen * sizeof(int));
    }

    MPI_Gather(sendbuffer, 2, MPI_INT, recvbuffer, 2, MPI_INT, 0, MPI_COMM_WORLD);
    if (myrank == 0)
    {
        printf("Process %d received: \n", myrank);
        for (int i = 0; i < recvbufflen; i++)
            printf("% d", recvbuffer[i]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}
