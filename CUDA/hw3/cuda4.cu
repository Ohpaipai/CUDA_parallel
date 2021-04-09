#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include<time.h>
#define blknum 1
#define threadnum 1024
#define N 10000000
__global__ void add( int *a, int *b, int *c ){
    int tid = threadIdx.y* blockDim.x + threadIdx.x;
	int blkid = blockDim.x;
	for(int i=tid;i<N;i+=blkid){
		//printf("%d\n",i);
		c[i] = a[i] + b[i];
	}
//	if(blkid<N)
//		c[blkid] = a[blkid]+b[blkid];
}


int main( void ) {
    int *a, *b, *c;
    int *dev_a, *dev_b, *dev_c;
	
    // allocate the memory on the CPU
    a = (int*)malloc( N * sizeof(int) );
    b = (int*)malloc( N * sizeof(int) );
    c = (int*)malloc( N * sizeof(int) );
	
    // allocate the memory on the GPU
    cudaMalloc( (void**)&dev_a, N * sizeof(int) );
    cudaMalloc( (void**)&dev_b, N * sizeof(int) );
    cudaMalloc( (void**)&dev_c, N * sizeof(int) );

    // fill the arrays 'a' and 'b' on the CPU
	srand ( time(NULL) );
    for (int i=0; i<N; i++) {
        a[i] = rand()%256;
        b[i] = rand()%256;
    }
    // copy the arrays 'a' and 'b' to the GPU
    cudaMemcpy( dev_a, a, N * sizeof(int), cudaMemcpyHostToDevice );
    cudaMemcpy( dev_b, b, N * sizeof(int), cudaMemcpyHostToDevice );
   
	/* Get start time event{{{*/
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);
	/*}}}*/
	

	
	//GPU kernel function
	   	 
	dim3 blocksize(64,16);
	add<<<blocknum,blocksize>>>( dev_a, dev_b, dev_c ); //1 block 1024 thread
    
	/* Get stop time event{{{*/
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop); 
	// Compute execution time
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("GPU time: %13f msec\n", elapsedTime);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	/*}}}*/
    
    // copy the array 'c' back from the GPU to the CPU
    cudaMemcpy( c, dev_c, N * sizeof(int), cudaMemcpyDeviceToHost );
    // verify that the GPU did the work we requested
    bool success = true;
    for (int i=0; i<N; i++) {
        if ((a[i] + b[i]) != c[i]) {
            printf( "Error:  %d + %d != %d\n", a[i], b[i], c[i] );
            success = false;
        }
    }
    if (success)    printf( "We did it!\n" );

    // free the memory allocated on the GPU
    cudaFree( dev_a );
    cudaFree( dev_b );
    cudaFree( dev_c );

    return 0;
}
