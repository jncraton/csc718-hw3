#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100000000

float a[VECLEN], b[VECLEN], sum;

float dotprod ()
{
int i,tid;
float tmp;
  omp_set_num_threads(4);
  #pragma omp parallel
  #pragma omp reduction (+ sum )
  for (i=0; i < VECLEN; i++)
    {
    tmp = a[i]*b[i];
    sum += tmp;
    }
}


int main (int argc, char *argv[]) {
int i;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

  dotprod();

printf("Sum = %f\n",sum);

}

