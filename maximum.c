#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415926
#define N 2000000
int rand_array[N];
int get_max_num(int start_num,int end_num)
{
    int max = -1;
    for(int p = start_num; p < end_num; p++)
    {
        if(rand_array[p] > max)
            max = rand_array[p];
    }
    return max;
}
int get_final_max_num(int x1,int x2,int x3,int x4)
{
    int max = x1;
    if(x2 > max)
        max = x2;
    if(x3 > max)
        max = x3;
    if(x4 > max)
        max = x4;
    return max;
}
int main(int argc,char **argv)
{
    for(int j = 0; j < N; j++)
    {
        rand_array[j] = rand();
    }
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    int size,rank,dest;
    char str[100];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    int max;
    if(rank==0)
    {
        int max1,max2,max3,max4;
        MPI_Recv(&max1,1,MPI_INT,1,1,comm,&status);
        MPI_Recv(&max2,1,MPI_INT,2,1,comm,&status);
        MPI_Recv(&max3,1,MPI_INT,3,1,comm,&status);
        MPI_Recv(&max4,1,MPI_INT,4,1,comm,&status);
        max = get_final_max_num(max1,max2,max3,max4);
        printf("the max num in array is : %d\n",max);
        MPI_Bcast(&max,1,MPI_INT,0,comm);

    }
    else 
    {
        int maxi=get_max_num(N/4*(rank-1),N/4*rank);
    MPI_Send(&maxi,1,MPI_INT,0,1,comm);
    printf("i am %d , my max num is %d\n",rank,maxi);
    MPI_Bcast(&max,1,MPI_INT,0,comm);
    printf("i am %d , the max num is %d\n",rank,max);
    }
    

    MPI_Finalize();
    return 0;
}

