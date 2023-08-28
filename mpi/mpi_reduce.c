#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAYSIZE 100




int main(int argc, char **argv)
{
    int size, rank, i = 0, localsum = 0, globalsum = 0;
    int data[ARRAYSIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(ARRAYSIZE%size != 0)
    {
        printf("O tamanho do array deve ser divisivel pelo numero de processos\n");
        MPI_Finalize();
        return 0;
    }

    int start = floor(rank * ARRAYSIZE / size);
    int end   = floor((rank + 1) * ARRAYSIZE / size) - 1;

    for (i = start; i <= end; i++)
    {
        data[i] = i * 2;
        localsum = localsum + data[i];
    }

    MPI_Reduce(&localsum, &globalsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("The global sum =%d\n", globalsum);

    MPI_Finalize();

}

// Exercicio:
// Modifique o programa acima para realizar a seguinte tarefa:
// 1. Processo zero deve:
//    criar o vetor data de tamanho ARRAYSIZE e inicializa-lo
// 2. Espalha-lo entre os processos
// 3. Todos os demais processos devem:  
//     receber o vetor data de tamanho ARRAYSIZE/NPROCS
// 4. Todos os processadores devem:
//     calcular a soma local
//     calcular a soma global
// 5. O processo zero deve:
//     imprimir a soma global

