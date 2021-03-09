#include<omp.h>
#include<stdio.h>
int main(int argc, char **argv){
 //example1 ~ 2.
/*	#pragma omp parallel for
//	{
		for(int i = 0; i <5; i++)
			printf("Thread %d loop%d\n", omp_get_thread_num(),i);
//	}
*/
 // example3.
 /*
	#pragma omp parallel sections
 	{
		#pragma omp section
     {
        for(int i=0;i<100000;++i)
        {}
        printf("thread %d , first section\n",omp_get_thread_num());
     }
     #pragma omp section
     {
        printf("thread %d , second section\n",omp_get_thread_num());
     }
     #pragma omp section
     {
        printf("thread %d , third section\n",omp_get_thread_num());
     }
     #pragma omp section
     {
		printf("thread %d , fourth section\n",omp_get_thread_num());
     }
  	}
	*/
// example4.
/*
	#pragma omp parallel
	{
		for(int i = 0; i <3; i++){
			for(int j = 0; j <100000; j++){}
			printf("Thread %d %d\n", omp_get_thread_num(),i);
		}
		printf("Thread %d two times\n", omp_get_thread_num());
		#pragma omp single
		{
			printf("Thread %d one times\n", omp_get_thread_num());
		}
		#pragma omp master
		{
			printf("Thread %d master\n", omp_get_thread_num());
		}
	}
*/
// example5.
/*	int i,j;
		#pragma omp parallel
	{
//		#pragma omp parallel for num_threads(8) collapse(8)
		#pragma omp for
		for(i=0;i<5;i++)
//			#pragma omp parallel for num_threads(8) collapse(8)
				for(j=0;j<5;j++)
					printf("thread %d : %d loop\n",omp_get_thread_num(),i*5+j);
	}*/
	int i, j;
	int *a;
	int b;
	a=&b;
	*a = 100000;
#pragma omp parallel for num_threads(2) private(j)
for (i = 0; i < 4; i++)
    for (j = 0; j <4; j++){
        printf("%d %d %d\n", i, j, omp_get_thread_num());
		(*a)++;
//		printf("Test %d\n",a);
	}
printf("%d\n",*a);
		printf("------------------------------------------------------------------------\n");
/*yy	#pragma omp parallel for private(j)
		for(i=0;i<5;i++)
				for(j=0;j<5;j++)
					printf("(private)thread %d : %d loop\n",omp_get_thread_num(),i*5+j);
*/	return 0;
}
