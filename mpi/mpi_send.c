#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;
    MPI_Status status;
    double vector[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (nprocs != 2)
    {
        printf("Este programa necessita de 2 processos\n");
        MPI_Finalize();
        return 0;
    }
    if (rank == 0)
    {
        for (int i = 0; i < 10; i++)
            vector[i] = 0.1 * i;
        MPI_Send(vector, 10, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
        printf("Enviado!\n"); 
    }
    else if (rank == 1)
    {
        MPI_Recv(vector, 10, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        printf("Recebido!\n");    
    }
    MPI_Finalize();
    return 0;
}
