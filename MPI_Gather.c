#include <stdio.h>
#include "mpi.h"
#include<string.h>
#include<malloc.h>
int main(int argc, char **argv)
{    
    int rank, size, sbuf[3], *rbuf, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (i = 0; i < 3; i++)
         sbuf[i] = rank * 10 + i;
    if (rank == 0)
      rbuf = (int*)malloc(sizeof(int) * 3 * size);
    MPI_Gather(sbuf, 3, MPI_INT, rbuf, 3, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0){
       printf("Process 0 receives:");
       for (i = 0; i < size * 3; i++)
         printf("%d ", rbuf[i]);
       putchar('\n');
    }
    MPI_Finalize();
    return 0;
 } 
