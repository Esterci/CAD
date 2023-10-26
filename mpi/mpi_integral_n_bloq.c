#include <mpi.h>
#include <math.h>
#include <stdio.h>

float integral(float ai, float h, int n);

void main(int argc, char *argv[])
{
  /***********************************************************************
   *                                                                     *
   *  This is a serial C-version of the MPI example on integration       *
   *  Compute \int_a^b{cos(x)dx}  using mid-point integration rule       *                                             *
   *                                                                     *
   ***********************************************************************/
  // variáveis para o MPI
  int numtasks, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // variáveis para o calculo da integral
  int n, i, j, ierr;
  float h, a, b, pi, my_int;

  pi = acos(-1.0);  /* = 3.14159... */
  a = 0.;           /* lower limit of integration */
  b = pi * 1. / 2.; /* upper limit of integration */
  // p = 4;               /* number of processes (partitions) */
  n = 500;                    /* number of increment within each process */
  h = (b - a) / n / numtasks; /* length of increment */

  float ai = a + rank * n * h; /* lower limit of integration for partition i */
  float integral_local[numtasks], integral_buf[numtasks-1];
  MPI_Request reqs[numtasks*2]; // required variable for non-blocking calls
  MPI_Status stats[numtasks*2]; // required variable for Waitall routine

  integral_local[rank] = integral(ai, h, n);
  
  printf("The integral of task %d, sum =%fn\n", rank, integral_local[rank]);

  if (rank == 0)
  {
    for (int i = 1; i < numtasks-1; i++)
    {
      MPI_Irecv(&integral_buf[i-1], 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &reqs[numtasks-1+i]);
    }
  }
  else
  {
    MPI_Isend(&integral_local[rank], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &reqs[rank-1]);
  }

  // wait for all non-blocking operations to complete
  MPI_Waitall(4, reqs, stats);

  for (int i = 0; i < numtasks; i++)
  {
    integral_local[0] += integral_buf[i];
  }

  printf("The integral sum =%fn\n", integral_local[0]);

  MPI_Finalize();
}

float integral(float ai, float h, int n)
{
  int j;
  float aij, integ;

  integ = 0.0; /* initialize    */
  for (j = 0; j < n; j++)
  {                           /* sum integrals */
    aij = ai + (j + 0.5) * h; /* mid-point     */
    integ += cos(aij) * h;
  }
  return integ;
}