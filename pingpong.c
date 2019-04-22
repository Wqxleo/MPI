#include <stdio.h>
#include "mpi.h"

int main(int argc,char **argv)
{
    int limit=10;
    int count=0;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    while(count<limit)
    {
        if(rank==0)
        {
            count++;
            MPI_Send(&count,1,MPI_INT,1,10,comm);
            printf("0 send %d to 1\n",count);

            MPI_Recv(&count,1,MPI_INT,1,20,comm,&status);
            printf("0 receive %d from 1\n",count);
        }
        else
        {
            MPI_Recv(&count,1,MPI_INT,0,10,comm,&status);
            printf("1 receive %d from 0\n",count);
            count++;
            MPI_Send(&count,1,MPI_INT,0,20,comm);
            printf("1 send %d to 0\n",count);
        }
    }
    MPI_Finalize();
}
