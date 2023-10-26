#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int numtasks, rank, dest, source, count, tag = 1;
    char inmsg = 'i', outmsg = 'o';
    MPI_Status Stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        dest = 1; // Tarefa zero 0 envia para tarefa 1
        source = 1;
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
    }
    else if (rank == 1)
    {
        dest = 0;
        source = 0; // Tarefa 1 recebe da tarefa 0
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }
    // Testa a variável Stat e imprime mensagem.
    MPI_Get_count(&Stat, MPI_CHAR, &count);

    if (rank == 0)
        printf("Task %d received %d char(s) from task %d with tag %d, msg: %c \n",
               rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG,inmsg);

    else if (rank == 1)
        printf("Task %d received %d char(s) from task %d with tag %d, msg: %c \n",
               rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG,outmsg);

    MPI_Finalize();
}
