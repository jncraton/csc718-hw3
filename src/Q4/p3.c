#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100000000

float a[VECLEN], b[VECLEN], sum;

float dotprod ()
{
int i,tid;
  #pragma omp parallel for
  for (i=0; i < VECLEN; i++)
    {
    a[i] = a[i]*b[i];
    }

  for (i=0; i < VECLEN; i++) sum+= a[i];
}


int main (int argc, char *argv[]) {
int i;

omp_set_num_threads(4);
#pragma omp parallel for
for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;

sum = 0.0;

  dotprod();

printf("Sum = %f\n",sum);

}

