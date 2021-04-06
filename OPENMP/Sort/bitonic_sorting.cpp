#include <iostream>
#include<omp.h>
#include<algorithm>
#include <time.h>
//#define N  1000000
//#define degree2ofN 1048576
#define N  8
#define degree2ofN 8
int array[degree2ofN];
void b_sort(int _start, int _length, bool _flag){

	std::cout<<"in flag = "<<_flag<<std::endl;
	//if(_length == 1)
	//	return;

	int i,j,k;
	if(_flag == true){ // Ascending
		k=1;
		for(i=_length/2;i>0;i/=2){ //need to change 距離差距 跟計次 如假設 交換為 0 2代表差距2 那這樣下次還要交換 0 1
			for(j = _start; i+j<_length; j++){//交換幾個
				std::cout<<"往上 change "<<j<<" & "<<i<<"\n";
				if(array[j]>array[i+j])
					std::swap(array[j],array[i+j]);
			}
			k*=2;
		}
	}
	else if(_flag==false){ //Descending 
//		std::cout<<"向下\n";
		k=1;
		for(i=_length/2;i>0;i/=2){
			for(j = _start; i+j<_length; j++){
				std::cout<<"length = "<<_length<<"  往下 change "<<j<<" & "<<i<<"\n";
				if(array[j]<array[i+j])
					std::swap(array[j],array[i+j]);
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
	int i, j;
	for(i=0; i<N;i++){
		array[i] = rand()%100;
		std::cout<<array[i]<<" ";
	}
	std::cout<<std::endl;
/*	for(i=N;i<degree2ofN-N;i++){
		array[i] = 1000001;
	}*/
	//start
	clock_gettime( CLOCK_REALTIME, &t_start);
	for( i=2;i<=degree2ofN;i*=2){ //最外層 每次做都是 2的次方
		for(j = 0; j <degree2ofN; j+=i){ //2每次交換的index差距
//			std::cout<<"("<<j<<"/"<<i<<")%2="<<(j/i)%2<<std::endl;
			int pn = (j/i)%2;
			if(pn==0){
		//		std::cout<<1<<std::endl;
				b_sort(j,i+j,true);
			}
			else{
		//		std::cout<<0<<std::endl;
				b_sort(j,i+j,false);
			}
		}
		std::cout<<" i = "<<i<<std::endl;
		for(int k=0; k<N;k++){
			std::cout<<array[k]<<" ";
		}
		std::cout<<std::endl;
	}
	for(i=0; i<N;i++){
		std::cout<<array[i]<<" ";
	}
	std::cout<<std::endl;
	//end
	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);
	return 0;
}
