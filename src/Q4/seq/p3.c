#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define VECLEN 100000000

double a[VECLEN], b[VECLEN], sum;

void dotprod ()
{
int i,tid;

  for (i=0; i < VECLEN; i++)
    {
    sum = sum + (a[i]*b[i]);
    }
}


int main (int argc, char *argv[]) {
int i;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

  double begin = omp_get_wtime();

  dotprod();
  double time_spent = (double)(omp_get_wtime() - begin);

  printf("Sum = %f\n",sum);
  printf ("Time: %f\n", time_spent);

}

