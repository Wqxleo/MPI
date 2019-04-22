#include<stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
int main(int argc, char** argv){
   int rank, size, *sbuf, *rbuf, i;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   sbuf = (int*)malloc(size * 3 * sizeof(int));
   rbuf = (int*)malloc(size * 3 * sizeof(int));
   for (i = 0; i < size * 3; i++)
      sbuf[i] = rank * 10 + i;
   printf("Before exchange, process %d has ", rank);
   for (i = 0; i < size * 3; i++)
      printf("%d ", sbuf[i]);
   putchar('\n'); 
MPI_Alltoall(sbuf, 3, MPI_INT, rbuf, 3, MPI_INT, MPI_COMM_WORLD);   printf("After exchange, process %d has ", rank);
   for (i = 0; i < size * 3; i++)
      printf("%d ", rbuf[i]);
   putchar('\n');
   MPI_Finalize();
   free(sbuf);
   free(rbuf);
   return 0; 
} 
