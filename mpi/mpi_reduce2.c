#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void onenorm(void *vin, void *vinout, int *len, MPI_Datatype *type)
{
    int i;
    float *in    = (float *)vin;
    float *inout = (float *)vinout;

    for (i = 0; i < *len; i++)
    {
        *inout = fabs(*in) + fabs(*inout);
        in++;
        inout++;
    }
}

int main(int argc, char *argv[])
{
    int root = 0, p, myid;
    float sendbuf, recvbuf;
    MPI_Op myop;
    int commute = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Op_create(onenorm, commute, &myop);

    sendbuf = myid * myid *(-1);

    printf("Process %d has %f\n", myid, sendbuf);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&sendbuf, &recvbuf, 1, MPI_FLOAT, myop, root, MPI_COMM_WORLD);
    if (myid == root)
        printf("The operation yields %f\n", recvbuf);
    MPI_Finalize();

    return 0;
}
