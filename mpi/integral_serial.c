#include <math.h>
#include <stdio.h>

float integral(float ai, float h, int n);

void main()
{
  /***********************************************************************
   *                                                                     *
   *  This is a serial C-version of the MPI example on integration       *
   *  Compute \int_a^b{cos(x)dx}  using mid-point integration rule       *                                             *
   *                                                                     *
   ***********************************************************************/

  int n, p, i, j, ierr;
  float h, integral_sum, a, b, pi, my_int;

  pi = acos(-1.0);     /* = 3.14159... */
  a = 0.;              /* lower limit of integration */
  b = pi * 1. / 2.;    /* upper limit of integration */
  p = 4;               /* number of processes (partitions) */
  n = 500;             /* number of increment within each process */
  h = (b - a) / n / p; /* length of increment */

  integral_sum = 0.0;

  /* sum of integrals over all processes */
  for (i = 0; i < p; i++)
  {
    float ai = a + i * n * h; /* lower limit of integration for partition i */
    integral_sum += integral(ai, h, n);
    printf("The integral sum =%fn\n", integral_sum);
  }

}

float integral(float ai, float h, int n)
{
  int j;
  float aij, integ;

  integ = 0.0; /* initialize    */
  for (j = 0; j < n; j++)
  {                           /* sum integrals */
    aij = ai + (j + 0.5) * h; /* mid-point     */
    integ += cosf(aij) * h;
  }
  return integ;
}