#include <iostream>
#include<omp.h>
#include<algorithm>
#include <time.h>
#define N 1000000
#define degree2ofN 1048576




int main(int argc, char** argv){
	
	struct timespec t_start, t_end;
	double elapsedTime;
	
	int array[degree2ofN];
	int i, j;
	for(i=0; i<N;i++){
		array[i] = rand()%1000000;		
	}
	for(i=N;i<degree2ofN-N;i++){
		array[i] = 1000001;
	}


	//start
	clock_gettime( CLOCK_REALTIME, &t_start);
	
	//end
	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);


}
