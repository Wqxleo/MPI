#include <stdio.h>
#include "mpi.h"
#include<string.h>
int main(int argc,char **argv)
{
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    int size,rank;
    char str[100];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    if(rank==0)
    {
        strcpy(str,"hello world");
        printf("Process 0 send 1 %s\n",str);
        MPI_Send(str,strlen(str)+1,MPI_CHAR,1,99,comm);
    }
    else if(rank==1)
    {
        MPI_Recv(str,100,MPI_CHAR,0,99,comm,&status);
        printf("Process 1 receives 0 %s\n",str);

    }
    MPI_Finalize();

}
