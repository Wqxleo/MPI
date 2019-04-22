#include<stdio.h>
#include "mpi.h"
#include "math.h"
int main(int argc,char **argv)
{
    int size, rank,n,p,i;
    double h;
    MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Status status;
    n = 4;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    h = M_PI/2/n;
    double sum = 0;
    double flag;
    double psum,total;
    switch(rank)
    {
    case 0:
        {
            flag = 0;
            break;
        }
    case 1:
        {
            flag = M_PI/2;
            break;
        }
    case 2:
        {
            flag = M_PI;
        }
    case 3:
        {
            flag = 1.5*M_PI;
        }
    }
    for(i = 0; i < n;i++)
        {
            sum += fabs(cos(flag+i*h+h/2.0)*h);
        }
    if(rank != 0)
    {
        MPI_Send(&sum, 1, MPI_DOUBLE, 0, 99, comm);
    }
    printf("part sum of process %d is %lf.\n", rank, sum);
    if(rank == 0)
    {
        total = sum;
        for(i = 1; i < 4; i++)
        {
            MPI_Recv(&psum, 1, MPI_DOUBLE, i, 99,  comm, &status);
            total += psum;
        }
        printf("sum is %lf.\n",total);

    }

    MPI_Finalize();
    return 0;
}
