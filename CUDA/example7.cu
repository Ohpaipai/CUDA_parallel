#include<stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define NUM_ROWS 4
#define NUM_COLS 4

 __global__ void add2(int* da, int* db, int* dc)
{
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;
    int id = idy * gridDim.x * blockDim.x  + idx;
    dc[id] = da[id]+ db[id];
}

int main()
{
    int	ha[NUM_ROWS][NUM_COLS] ;
    int	*da ;
    int	hb[NUM_ROWS][NUM_COLS] ;
    int *db;
    int	hc[NUM_ROWS][NUM_COLS] ;
    int *dc;
	
    int iSize = NUM_ROWS * NUM_COLS * sizeof(int) ;
    cudaError_t     cuError = cudaSuccess;
	
    dim3 dimGrid (NUM_ROWS/2, NUM_COLS/2, 1) ;
    dim3 dimBlock (NUM_ROWS/2, NUM_COLS/2, 1) ;

    for(int i=0;i<NUM_ROWS;i++)
    {
        for(int j=0;j<NUM_COLS;j++)
        {
            ha[i][j]=rand()%10+1;
	    hb[i][j]=rand()%10+1;
        }
    }

    cuError = cudaMalloc((void**)&da, iSize) ;
    if (cudaSuccess != cuError)
    {
        printf ("Failed to allocate memory\n") ;
        return 1 ;
    }
    cuError = cudaMemcpy(da, ha, iSize, cudaMemcpyHostToDevice);
    if (cudaSuccess != cuError)
    {
        cudaFree (da) ;
        printf ("Failed in Memcpy 1\n") ;
        return 1 ;
    }
	
    cuError = cudaMalloc((void**)&db, iSize) ;
    if (cudaSuccess != cuError)
    {
        printf ("Failed to allocate memory\n") ;
        return 1 ;
    }
    cuError = cudaMemcpy(db, hb, iSize, cudaMemcpyHostToDevice);
    if (cudaSuccess != cuError)
    {
        cudaFree (db) ;
        printf ("Failed in Memcpy 1\n") ;
        return 1 ;
    }
    cuError = cudaMalloc((void**)&dc, iSize) ;
    if (cudaSuccess != cuError)
    {
        printf ("Failed to allocate memory\n") ;
        return 1 ;
    }


    add2<<<dimGrid, dimBlock>>>(da, db, dc);
	
    cuError = cudaGetLastError () ;
    if (cudaSuccess != cuError)
    {
            printf ("Failed in kernel launch and reason is %s\n", cudaGetErrorString(cuError)) ;
            return 1 ;
    }

    cuError = cudaMemcpy(hc, dc, iSize, cudaMemcpyDeviceToHost);
    if (cudaSuccess != cuError)
    {
            cudaFree (dc) ;
            printf ("Failed in Memcpy 2\n") ;
            return 1 ;
    }

    bool success = true;
    for(int i=0;i<NUM_ROWS;i++){
        for(int j=0;j<NUM_COLS;j++){
            if ((ha[i][j] + hb[i][j]) != hc[i][j]) {
		 printf( "Error:  %d + %d != %d\n", ha[i][j], hb[i][j], hc[i][j] );
		 success = false;
	    } 
	}
    }
    if (success)    printf( "We did it!\n" );
	
    cudaFree (da) ;
    cudaFree (db) ;	
    cudaFree (dc) ;

    return 0;
}
