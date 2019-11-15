
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main (int argc, char *argv[])
{
	int   i, n;
	float a[1000000], b[1000000], sum;

	/* Some initializations */
	n = 1000000;
	for (i=0; i < n; i++)
		a[i] = b[i] = i * 1.0;

	sum = 0.0;

  clock_t begin = clock();

  	for (i=0; i < n; i++)
		sum = sum + (a[i] * b[i]*b[i]*b[i]);

  double time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;

	printf("   Sum = %f\n",sum);
  printf ("Time: %f\n", time_spent);
	return 0;
}
