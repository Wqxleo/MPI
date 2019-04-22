#include<stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
struct DATATYPE
{
    int rank;
    int val;
};
int main(int argc,char **argv)
{
    struct DATATYPE sbuf;
    struct DATATYPE rbuf[4];
    int ranking[4];
    int size, rank,n,p,i,j,rank_rbuf;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);
    sbuf.rank = rank;
    srand(rank);//设置当前时间为种子
    sbuf.val = rand()%10+1;//产生1~10的随机数
    printf("process %d speed is %d\n",rank,sbuf.val);

    
    MPI_Gather(&sbuf,1,MPI_2INT,rbuf,1,MPI_2INT,0,comm);
    if(rank == 0)
    {
        struct DATATYPE temp;
        for(i = 1; i < 4; i++)
            for(j = 0; j < 4-i; j++)
        {
            if(rbuf[j].val < rbuf[j+1].val)
            {
                temp = rbuf[j];
                rbuf[j] = rbuf[j+1];
                rbuf[j+1] = temp;
            }
        }

        for(i = 0; i < 4; i++)
        {
            ranking[rbuf[i].rank] = i+1;
        }
    }
    MPI_Scatter(ranking, 1, MPI_INT, &rank_rbuf, 1, MPI_INT,0, comm);
    printf("process %d ranking is %d\n",rank,rank_rbuf);
    MPI_Finalize();
    return 0;
}
