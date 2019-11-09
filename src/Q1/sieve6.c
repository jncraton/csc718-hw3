/* Sieve of eratosthenes */
#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//#include "MyMPI.h"

#define MIN(a,b)  ((a)<(b)?(a):(b))
#define BLOCK_LOW(id,p,n)  ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW(((id)+1),p,n)-1)
#define BLOCK_SIZE(id,p,n) ((BLOCK_LOW(((id)+1),p,n))-(BLOCK_LOW(id,p,n)))
#define BLOCK_OWNER(index,p,n) (((p)*(index)+1)-1)/(n))

int main (int argc, char *argv[])
{
 int count;		/* local prime count	*/
 double elapsed_time; /* execution time	*/
 int first;		/* index of the first sieve	*/
 int global_count;	/* global count of prime numbers */
 int high_value; 	/* highest value assigned to this process */
 int i;		/* loop counter		*/
 int id;		/* this process id	*/
 int index;		/* index of the current sieve	*/
 int low_value;	/* lowest value assigned to this process */
 char *marked;		/* array elements to be  marked	*/
 char *sieves;		/* array of sieving primes from k -> sqrt(n)	*/
 int n;		/* value of the largest number	*/
 int sqrtN;		/* square root of n	*/
 int p; 		/* number of processes		*/
 int proc0_size;	/* number of elements assigned to process zero */
			/* this is to find if process zero has all primes */
 int prime;		/* current prime or sieve	*/
 int size;		/* elements in marked array 	*/

 MPI_Init (&argc, &argv);
 /* start timer */
 MPI_Barrier(MPI_COMM_WORLD);
 elapsed_time = -MPI_Wtime();
 MPI_Comm_rank (MPI_COMM_WORLD, &id);
 MPI_Comm_size (MPI_COMM_WORLD, &p);

 if (argc != 2)
 {
  if (!id)
   printf ("Command line: %s <m>\n", argv[0]);

  MPI_Finalize();
  exit (1);
 }

 n = atoi(argv[1]);

 /* find how many elements are assigned to this process */
 low_value = 2 + BLOCK_LOW(id,p,n-1);
 int proc_low = low_value;
 high_value = 2 + BLOCK_HIGH(id,p,n-1);
 size = BLOCK_SIZE(id,p,n-1);
 proc0_size = (n-1)/p;
 sqrtN = (int) sqrt((double) n);
 if ((2 + proc0_size) < sqrtN)
 {
  if (!id)
   printf ("Too many processes\n");

  MPI_Finalize();
  exit (1);
 }

 marked = (char *) malloc (size * sizeof(char));
 sieves = (char *) malloc ((sqrtN) * sizeof(char));

 if ((marked == NULL) || (sieves == NULL))
 {
  printf ("Cannot allocate enough memory\n");
  MPI_Finalize();
  exit (1);
 }

 if (!id)
  marked[0] = 0;

 for (i=0;i<size;i++) marked[i] = 0;
 marked[0] = 1;
 for (i=0;i<sqrtN;i++) sieves[i] = 0;
 sieves[0] = 1;

 //Create a list of sieving primes on each process from 2 -> SQRT(n)
 sieves[0] = 0;
 index = 1;
 prime = 3;
 do 
 {
  for(i=prime+prime+prime; i<(sqrtN-2); i+=prime<<1) {
    sieves[i>>1] = 1;
  }
  while (sieves[index]) index++;
  prime = (index<<1) + 1;
  index++;
 } while (prime * prime <= sqrtN);

 // Split into blocks to make use of cache locality
 int blocksize = 1024 * 128 * 2 * 4 * 8 / sizeof(int);
 int block_start = 0;
 for (low_value; low_value <= high_value; low_value+=blocksize) {
   index = 2;
   prime = 3;
   int inner_size = high_value - low_value;
   if (inner_size > blocksize) inner_size = blocksize;
  
   if (low_value & 1) low_value--;

   do {
    if (prime * prime > low_value)
     first = prime * prime - low_value;
    else {
     if (!(low_value % prime)) first = 0;
     else first = prime - (low_value % prime);
    }
    if (!(first & 1)) first += prime;
    for (i = first; i <= inner_size; i += prime<<1) {
      char offset = ((i+block_start) >> 1) & 0b111;
      marked[(i+block_start)>>4] = 
        marked[(i+block_start)>>4] | (1 << offset);
    }
  
    while (sieves[index]) index++;
    prime = (index<<1) + 1;
    index += 1;
   } while (prime * prime <= n);
  
   block_start += blocksize;
 }

 //Count the primes in each process 
 count = 0;
 for (i = 0; i < size/16+1; i++) {
    count += 
      !(marked[i] & 0b00000001) +
      !(marked[i] & 0b00000010) +
      !(marked[i] & 0b00000100) +
      !(marked[i] & 0b00001000) +
      !(marked[i] & 0b00010000) +
      !(marked[i] & 0b00100000) +
      !(marked[i] & 0b01000000) +
      !(marked[i] & 0b10000000);
 }

 //SUM each count into process 0.
 MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

 elapsed_time += MPI_Wtime();

 if (!id) {
  printf ("%d primes are less than or equal to %d\n", global_count + 2, n);
  printf ("Total elapsed time: %10.6f\n", elapsed_time);
 }

 MPI_Finalize ();

 return 0;
}

