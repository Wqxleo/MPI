#include <stdio.h>
#include "mpi.h"
int main(int argc, char** argv){
   int rank,size,i;
   MPI_Comm comm = MPI_COMM_WORLD;
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   m1 = rand()%10;
   m2 = rand()%10;
   MPI_Reduce(&m1,rebuf, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
   MPI_Reduce(&m2,rebuf, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
   if(rank == 0)
   {
       printf("%d\n%d\n",rebuf[0],rebuf[1]);
   }
   MPI_Finalize();
   return 0;
}
