#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include<math.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

float *creat_rand_nums(int num_elements)
{
    float *rand_nums=(float *)malloc(sizeof(float)*num_elements);
    
    int i;
    for(i=0;i<num_elements;i++)
    {
        rand_nums[i]=(rand()/(float)RAND_MAX);//rand产生0到RAND_MAX之间的随机数，然后除以RAND_MAX就得到0-1之间的随机数

    }
    return rand_nums;
}
float compute_avg(float *array,int num_elements)
{
    float sum=0.f;
    int i;
    for(i=0;i<num_elements;i++)
    {
        sum+=array[i];
    }
    return sum/num_elements;
}
int main(int argc,char **argv)
{
    MPI_Init(&argc,&argv);
    if(argc!=2)
    {
        fprintf(stderr,"Usage:avg num_elements_per_proc\n");
        exit(1);
    }
    int num_elements_per_proc=atoi(argv[1]);
    srand(time(NULL));
    MPI_Init(NULL,NULL);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;
    int size,rank;
    MPI_Comm_size(comm,&size);
    MPI_Comm_rank(comm,&rank);

    float *rand_nums=NULL;
    if(rank==0)
    {
        rand_nums=creat_rand_nums(num_elements_per_proc*size);

    }
    float *sub_rand_nums=(float *)malloc(sizeof(float)*num_elements_per_proc);
    
    MPI_Scatter(rand_nums,num_elements_per_proc,MPI_FLOAT,sub_rand_nums,num_elements_per_proc,MPI_FLOAT,0,comm);


    float sub_avg=compute_avg(sub_rand_nums,num_elements_per_proc);
    float *sub_avgs=NULL;
    if(rank==0)
    {
        sub_avgs=(float *)malloc(sizeof(float)*size);
        
    }
    MPI_Gather(&sub_avg,1,MPI_FLOAT,sub_avgs,1,MPI_FLOAT,0,comm);

    if(rank==0)
    {
        float avg=compute_avg(sub_avgs,size);
        printf("Avg of all elements is %f\n",avg);
        float original_data_avg=compute_avg(rand_nums,num_elements_per_proc*size);
        printf("Avg computed across original data is %f\n",original_data_avg);
    }

    if(rank==0)
    {
        free(rand_nums);
        free(sub_avgs);
    }
    free(sub_rand_nums);
    MPI_Barrier(comm);
    MPI_Finalize();
    return 0;
}

