
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 620                 /* number of rows in matrix A */
#define NCA 150                 /* number of columns in matrix A */
#define NCB 70                  /* number of columns in matrix B */

int main (int argc, char *argv[])
{
int	tid, nthreads, i, j, k, chunk;
double	a[NRA][NCA],           /* matrix A to be multiplied */
	b[NCA][NCB],           /* matrix B to be multiplied */
	c[NRA][NCB];           /* result matrix C */

chunk = 10;                    /* set loop iteration chunk size */


  /*** Initialize matrices ***/
  
  for (i=0; i<NRA; i++) {
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  }
  
  for (i=0; i<NCA; i++) {
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;
  }

  for (i=0; i<NRA; i++) {
    for (j=0; j<NCB; j++)
      c[i][j]= 0;
  }

  omp_set_num_threads(4);

  for (k=0; k<NCA; k++) {
    #pragma omp parallel for private(i)
    for (j=0; j<NCB; j++) {
      for (i=0; i<NRA; i++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  {

/*** Print results ***/
printf("******************************************************\n");
printf("Result Matrix:\n");
for (i=0; i<NRA; i++)
  {
  for (j=0; j<NCB; j++)
    printf("%6.2f   ", c[i][j]);
  printf("\n");
  }
printf("******************************************************\n");
printf ("Done.\n");
}
}
