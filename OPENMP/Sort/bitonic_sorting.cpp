#include <iostream>
#include<omp.h>
#include<algorithm>
#include<time.h>
//#define N  1000000
//#define degree2ofN 1048576
#define N  1000000
#define degree2ofN 1048576
int array[degree2ofN];
int s_array[degree2ofN];
void b_sort(int _start, int _length, bool _flag){
	int i,j,k;
	int count;
	int _num = _length -_start;
	if(_flag == true){ // Ascending
		for(i=_num/2;i>0;i/=2){ //need to change 距離差距 跟計次 如假設 交換為 0 2代表差距2 那這樣下次還要交換 0 1
			count =0;
			for(j = _start; i+j<_length; j++){//交換幾個
				if(count < i){
					if(array[j]>array[i+j])
						std::swap(array[j],array[i+j]);
					count++;
				}
				else{
					count = 0;
					j=i+j-1;  //直接跳躍調 我換過的地方 假如式 2 跳過 2不換 式1 跳過1不換 (-1 是因為下次會+1)
				}
			}
			k*=2;
		}
	}
	else if(_flag==false){ //Descending 
//		std::cout<<"向下\n";
		k=1;
		for(i=_num/2;i>0;i/=2){
			count =0;
			for(j = _start; i+j<_length; j++){
				if(count < i){
					if(array[j]<array[i+j])
						std::swap(array[j],array[i+j]);
					count++;
				}
				else{
					count = 0;
					j=i+j-1;
				}
			}
			k*=2;
		}
	}
}
int main(int argc, char** argv){
	struct timespec t_start, t_end;
	double elapsedTime;
	int numThreads =  omp_get_max_threads(); //get computer thread
	// set NUM
	long long int i, j;
	for(i=0; i<N;i++){
		array[i] = rand()%1000000;
		s_array[i] = array[i];
	}
	bool c=true;
	for(i=0; i<N; i++){
		if(array[i]!=s_array[i]){
			c=false;
			break;
		}
	}
	if(c)
		std::cout<<"True\n";
	else
		std::cout<<"False\n";

	for(i=N;i<degree2ofN;i++){
		array[i] = 1000000 + i ;
//		std::cout<<array[i]<<" ";
	}
	std::sort(s_array,s_array + N);
	//start
	clock_gettime( CLOCK_REALTIME, &t_start);
	for( i=2;i<=degree2ofN;i*=2){ //最外層 每次做都是 2的次方
		#pragma omp parallel for private(j)
		for(j = 0; j <degree2ofN; j+=i){ //2每次交換的index差距
			int pn = (j/i)%2;
			if(pn==0){
				b_sort(j,i+j,true);
			}
			else{
				b_sort(j,i+j,false);
			}
		}
	}
	//end
	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);
	for(i=0; i<N; i++){
		if(array[i]!=s_array[i]){
			c=false;
			break;
		}
	}
	if(c)
		std::cout<<"True\n";
	else
		std::cout<<"False\n";
/*	for(i=N;i<(degree2ofN-N);i++){
		std::cout<<array[i]<<" ";
	}*/
//	std::cout<<std::endl;
	return 0;
}
