
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{
	int   i, n;
	float a[1000000], b[1000000], sum;

	/* Some initializations */
	n = 1000000;
  omp_set_num_threads(4);

  #pragma omp parallel for
	for (i=0; i < n; i++)
		a[i] = b[i] = i * 1.0;

	sum = 0.0;

  #pragma omp parallel for
	for (i=0; i < n; i++) {
	  a[i] = (a[i] * b[i]*b[i]*b[i]);
  }

	for (i=0; i < n; i++) {
	  sum += a[i];
	}
  
	printf("   Sum = %f\n",sum);
}
