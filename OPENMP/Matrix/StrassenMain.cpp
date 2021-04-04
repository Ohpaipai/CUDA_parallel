#include"Strassen.h"
#include<time.h>
#define N 2048
/*{{{*/
void Strassen(int _n, Matrix &_A, Matrix &_B, Matrix &_C){
	int halfsize=_n/2;
	//128
	if( _n<=128){
//		std::cout<<_A<<"\n"<<_B<<"\n";
		_C=_A*_B;
	}
	else{
		Matrix A11(halfsize); Matrix A12(halfsize); Matrix A21(halfsize); Matrix A22(halfsize);
		Matrix B11(halfsize); Matrix B12(halfsize); Matrix B21(halfsize); Matrix B22(halfsize);
		Matrix C11(halfsize); Matrix C12(halfsize); Matrix C21(halfsize); Matrix C22(halfsize);
		Matrix M1(halfsize); Matrix M2(halfsize); Matrix M3(halfsize); Matrix M4(halfsize); Matrix M5(halfsize); Matrix M6(halfsize); Matrix M7(halfsize);
	//	Matrix AA(halfsize); Matrix BB(halfsize);	
		Matrix AA1(halfsize); Matrix AA2(halfsize); Matrix AA3(halfsize); Matrix AA4(halfsize); Matrix AA5(halfsize);
		Matrix BB1(halfsize); Matrix BB2(halfsize); Matrix BB3(halfsize); Matrix BB4(halfsize); Matrix BB5(halfsize);
		int i,j;
		/*Matrix be seprated to 4 Matrixs*/
		#pragma omp parallel for private(j)
		for(i=0; i<_n/2; i++){
			for(j=0; j<_n/2; j++){
				A11.M[i][j] = _A.M[i][j];
				A12.M[i][j] = _A.M[i][j+_n/2];
				A21.M[i][j] = _A.M[i+_n/2][j];
				A22.M[i][j] = _A.M[i+_n/2][j+_n/2];
				
				B11.M[i][j] = _B.M[i][j];
				B12.M[i][j] = _B.M[i][j+_n/2];
				B21.M[i][j] = _B.M[i+_n/2][j];
				B22.M[i][j] = _B.M[i+_n/2][j+_n/2];
			}
		}
/*	
 		std::cout<<"A=\n";
		std::cout <<A11 << std::endl<<A12<<std::endl<<A21<<std::endl<<A22<<std::endl;
		std::cout<<"B=\n";
		std::cout <<B11 << std::endl<<B12<<std::endl<<B21<<std::endl<<B22<<std::endl;
*/
		#pragma omp sections
		{
			#pragma omp section
			{
				//M1=(A11+A22)*(B11+B22)
				AA1=A11+A22;
				BB1=B11+B22;
			}
			#pragma omp section
			{
				//M2=(A21+A22)*B11
				AA2=A21+A22;
			}
			#pragma omp section
			{
				//M3=A11*(B12-B22)
				BB2=B12-B22;
			}
			#pragma omp section
			{
				//M4=A22*(B21-B11)
				BB3=B21-B11;
			}
			#pragma omp section
			{
				//M5=(A11+A12)*B22
				AA3=A11+A12;
			}
			#pragma omp section
			{
				//M6=(A21-A11)*(B11+B22)
				AA4=A21-A11;
				BB4=B11+B12;
			}
			#pragma omp section
			{
				//M7=(A12-A22)*(B21+B22)
				AA5=A12-A22;
				BB5=B21+B22;
			}
		}
		
		/*Alg*/
		//M1=(A11+A22)*(B11+B22)
		//AA=A11+A22; //AA1
		//BB=B11+B22; //BB1
//		#pragma omp task shared(M1) 
//		#pragma omp task 
		//Strassen(halfsize, AA, BB, M1);
//		#pragma omp sections
//			#pragma omp section
		Strassen(halfsize, AA1, BB1, M1);	
		//M2=(A21+A22)*B11
		//AA=A21+A22; //AA2
//		#pragma omp task shared(M2)
//		#pragma omp task 
		//Strassen(halfsize, AA, B11, M2);
//			#pragma omp section
		Strassen(halfsize, AA2, B11, M2);
		//M3=A11*(B12-B22)
		//BB=B12-B22; //BB2
//		#pragma omp task shared(M3)
//		#pragma omp task 
		//Strassen(halfsize, A11, BB, M3);
//			#pragma omp section
		Strassen(halfsize, A11, BB2, M3);
		//M4=A22*(B21-B11)
		//BB=B21-B11; //BB3
//		#pragma omp task shared(M4)
//		#pragma omp task 
		//Strassen(halfsize, A22, BB, M4);
//			#pragma omp section
		Strassen(halfsize, A22, BB3, M4);
		//M5=(A11+A12)*B22
		//AA=A11+A12; //AA3
//		#pragma omp task shared(M5)
//		#pragma omp task 
		//Strassen(halfsize, AA, B22, M5);
//			#pragma omp section
		Strassen(halfsize, AA3, B22, M5);
		//M6=(A21-A11)*(B11+B22)
		//AA=A21-A11; //AA4
		//BB=B11+B12; //BB4
//		#pragma omp task shared(M6)
//		#pragma omp task 
		//Strassen(halfsize, AA, BB, M6);
//			#pragma omp section
		Strassen(halfsize, AA4, BB4, M6);
		//M7=(A12-A22)*(B21+B22)
		//AA=A12-A22; //AA5
		//BB=B21+B22; //BB5
//		#pragma omp task shared(M7)
//		#pragma omp task 
		//Strassen(halfsize, AA, BB, M7);
//			#pragma omp section
		Strassen(halfsize, AA5, BB5, M7);
		





		#pragma omp sections
		{
			#pragma omp section
			{
				C11=M1+M4-M5+M7;
			}
			#pragma omp section
			{
				C12=M3+M5;
			}
			#pragma omp section
			{
				C21=M2+M4;
			}
			#pragma omp section
			{
				C22=M1+M3-M2+M6;
			}
		}	
		/*Merge*/
		#pragma omp parallel for private(j)
		for(i=0; i<halfsize; i++){
			for(j=0; j<halfsize; j++){
				_C.M[i][j] = C11.M[i][j];
				_C.M[i][j+_n/2] = C12.M[i][j];
				_C.M[i+_n/2][j] = C21.M[i][j];
				_C.M[i+_n/2][j+_n/2] = C22.M[i][j];
			}
		}
		/*
		A11.Delete(); A12.Delete(); A21.Delete(); A22.Delete();
		B11.Delete(); B12.Delete(); B21.Delete(); B22.Delete();
		M1.Delete(); M2.Delete(); M3.Delete(); M4.Delete(); M5.Delete(); M6.Delete(); M7.Delete();
		AA.Delete(); BB.Delete();
		*/
		
	}

}
/*}}}*/

int main(){
	struct timespec t_start, t_end;
	double elapsedTime;
	int i, j, k;
	int temp;
	
	Matrix A(N); Matrix BS(N); Matrix B(N); Matrix CS(N); Matrix C(N);
	
	//generate CASE	
	for( i=0; i<N; i++ ){
		for( j=0; j<N; j++ ) {
			A.M[i][j] = rand()%10;
			B.M[i][j] = rand()%10;
		}
	}
//	std::cout<<A<<"\n"<<B<<std::endl;
	//copy
	BS=B;
	/*Sequintal*/
	clock_gettime( CLOCK_REALTIME, &t_start);
  		//transpose of b
		for( i=0; i<N; i++ ){
			for( j=i; j<N; j++ ) {
				temp = BS.M[j][i];
				BS.M[j][i] = BS.M[i][j];
				BS.M[i][j] = temp;
			}
		}

	//std::cout<<"BS=\n"<<BS<<"\n";

		for( i=0; i<N; i++ ){
			for( j=0; j<N; j++ ) {
				CS.M[i][j] = 0;
				for( k=0; k<N; k++ ){
					CS.M[i][j] += A.M[i][k]*BS.M[j][k];
//					std::cout<<CS.M[i][j]<<std::endl;
				}
			}
		}
//	std::cout<<CS;

	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Sequential elapsedTime: %lf ms\n", elapsedTime);

	/*Strassen*/
	clock_gettime( CLOCK_REALTIME, &t_start);
	Strassen(N,A,B,C);
	// stop time
	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Strassen elapsedTime: %lf ms\n", elapsedTime);


//	std::cout<<C<<"\n"<<CS;
	if(CS==C)
		std::cout<<"True\n";
	else
		std::cout<<"Error\n";
   return 0;
}

