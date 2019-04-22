#include <stdio.h>
#include "mpi.h"
#include<string.h>
#include<malloc.h>
int main(int argc, char **argv){
    int rank, size, sbuf[3], *rbuf, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (i = 0; i < 3; i++)
         sbuf[i] = rank * 10 + i;
    rbuf = (int*)malloc(sizeof(int) * 3 * size);
    MPI_Allgather(sbuf, 3, MPI_INT, rbuf, 3, MPI_INT, MPI_COMM_WORLD);    printf("Process %d receives:", rank);
    for (i = 0; i < size * 3; i++)
      printf("%d ", rbuf[i]);
    putchar('\n');
    free(rbuf);
    MPI_Finalize();
    return 0; } 
