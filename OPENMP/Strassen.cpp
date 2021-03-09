#include<iostream>
#include<omp.h>
#include<stdio.h>
#include<time.h>

#define N 100




typedef struct Matrix{
	int MX[N][N];
} M;

int main(){
	struct timespec t_start, t_end;
	double elapsedTime;
	int i, j, k;
	int temp;
	M A,B,C;
	;
	for( i=0; i<N; i++ ){
		for( j=0; j<N; j++ ) {
			A.MX[i][j] = rand()%10;
			B.MX[i][j] = rand()%10;
		}
	}
	clock_gettime( CLOCK_REALTIME, &t_start);
   	//transpose of b
	for( i=0; i<N; i++ ){
		for( j=i+1; j<N; j++ ) {
			temp = B.MX[j][i];
			B.MX[j][i] = B.MX[i][j];
			B.MX[i][j] = temp;
		}
	}
	for( i=0; i<N; i++ ){
		for( j=0; j<N; j++ ) {
			C.MX[i][j] = 0;
			for( k=0; k<N; k++ ){
				C.MX[i][j] += A.MX[i][k]*B.MX[j][k];
			}
//			printf("C[%d , %d]=%d\n",i,j,C.MX[i][j]);
		}
	}
	// stop time
	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);


   return 0;
}

