#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VECLEN 100000000

double *a, *b, sum;

double begin;
double time_spent;

int main (int argc, char *argv[]) {
  int i;
  sum = 0.0;

  a = aligned_alloc(64, VECLEN * sizeof(double));
  b = aligned_alloc(64, VECLEN * sizeof(double));

  for (i=0; i < VECLEN; i++)
    a[i] = b[i] = 1.0 * i;

  omp_set_num_threads(4);

  begin = omp_get_wtime();

  #pragma omp parallel for reduction(+:sum) schedule(static)
  for (i=0; i < VECLEN; i+=1) {
    sum = sum + (a[i]*b[i]);
  }

  time_spent = (double)(omp_get_wtime() - begin);

  printf("Sum = %f\n",sum);
  printf ("Time: %f\n", time_spent);
}

