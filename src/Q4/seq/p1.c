#include <stdio.h>
#include <omp.h>
#define INTERVALS 1000000

int main(int arc, char* argv[])
{
	double area;	/* The final anser */
	double ysum;	/* Sum of rectangle heights */
	double xi;	/* Midpoint of interval */
	int i;	

	ysum = 0.0;

  double begin = omp_get_wtime();

	for (i=0; i < INTERVALS; i++)
	{
		xi=((1.0/INTERVALS)*(i+0.5));
		ysum+=4.0/(1.0+xi*xi);
	}

	area = ysum * (1.0/INTERVALS);

  double time_spent = (double)(omp_get_wtime() - begin);

	printf("pi is %13.11f\n", area);

  printf ("Time: %f\n", time_spent);
	return 0;
}
