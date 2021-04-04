#include<stdio.h>
#include<time.h>
#include<omp.h>
#define N 30
int fib_ser(int n){
	if(n<2)
		return 2;
	else
		return fib_ser(n-1) + fib_ser(n-2);
}

long long int fib(int n){
	long long int i ,j;
	if(n==0)
		return 1;
	else if(n==1)
		return 1;
	else{
			int a=0; 
			#pragma omp parallel for firstprivate(a) lastprivate(a)
				a+=fib(l);
		return a;
	}
}

long long int fib_s(int n){
	int i ,j;
	if(n==0)
		return 1;
	else if(n==1)
		return 1;
	else{

		long long i=fib_s(n-1);
		long long j=fib_s(n-2);
		//printf("Fib%d + Fib%d = %lld\n",(n-1),(n-2),i+j);
		return i+j;
	}
}

int main(){
	struct timespec t_start, t_end;
	double elapsedTime;
	clock_gettime( CLOCK_REALTIME, &t_start);
	printf("T_s %lld\n",fib_s(N));
	clock_gettime( CLOCK_REALTIME, &t_end);
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);

	clock_gettime( CLOCK_REALTIME, &t_start);
	printf("T %lld\n",fib(N));
	clock_gettime( CLOCK_REALTIME, &t_end);
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);
	
	return 0;
}
