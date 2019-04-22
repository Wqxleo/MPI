#include <stdio.h>
#include "mpi.h"

int main(int argc,char **argv)
{

    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    int size,rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    int source,dest,token;
    source=rank==0?size-1:rank-1;
    dest=(rank+1)%size;
    token=100;
    if(rank==0)
    {
        MPI_Ssend(&token,1,MPI_INT,dest,1,comm);
        printf("Process %d send token to %d\n",rank,dest);
        MPI_Recv(&token,1,MPI_INT,source,1,comm,&status);
        printf("Process %d receive token from %d\n",rank,source);
    }
    else
    {
        MPI_Recv(&token,1,MPI_INT,source,1,comm,&status);
        printf("Process %d receive token from %d\n",rank,source);
        MPI_Ssend(&token,1,MPI_INT,dest,1,comm);
        printf("Process %d send token to %d\n",rank,dest);
    }
    MPI_Finalize();
}
