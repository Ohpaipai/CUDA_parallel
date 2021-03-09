#include<iostream>
#include<omp.h>
#include<stdio.h>
#include<time.h>
#define N 2048
//Matrix define
typedef struct Matrix{
	int MX[N][N]={0};
	int size=N;
	
	Matrix operator=(Matrix a){
		int i,j;
		#pragma omp parallel for private(j)
		for(i=0; i<size; i++)
			for(j=0; j<size; j++){
				MX[i][j]=a.MX[i][j];
			}
			size = a.size;
		return *this;
	}
	// +
	Matrix operator+(Matrix a){
		int i,j;
		Matrix R;
		#pragma omp parallel for private(j)
		for(i=0; i<size; i++)
			for(j=0; j<size; j++){
				R.MX[i][j]=MX[i][j]+a.MX[i][j];
			}
		R.size=a.size;
		return R;
	}
	// -
	 Matrix operator-(Matrix a){
		int i,j;
		Matrix R;
		#pragma omp parallel for private(j)
		for(i=0; i<size; i++)
			for(j=0; j<size; j++){
				R.MX[i][j]=MX[i][j]-a.MX[i][j];
			}
		R.size=a.size;
		return R;
	}
	// *
 	Matrix operator*(Matrix a){
		int i,j,k;
		Matrix R;
		#pragma omp parallel for private(j) private(k)
		for(i=0; i<size; i++)
			for(j=0; j<size; j++){
				R.MX[i][j]=0;
				for(k=0; k<size; k++){
					R.MX[i][j]+=MX[i][k]*a.MX[k][j];
				}
			}
		R.size=a.size;
		return R;
	}
} M;
	
	std::ostream& operator<<(std::ostream &output, const M &a){
		for(int i=0; i<a.size; i++){
			for(int j=0; j<a.size; j++){
				output<<a.MX[i][j]<<" ";
			}
			output << "\n";
		}
		return output;	
	}

void Strassen(int n, M &A, M &B, M &C){
	
	
	if(n==2){
		C=A*B;
	//	std::cout<<A.size<<"  "<<B.size<<" "<<C.size<<std::endl;
	//std::cout<<"A=\n"<<A<<" ----------------------------\nB=\n"<<B<<"-----------------------------\nC=\n"<<C<<std::endl;
	}
	else{
		//divied and counter
		M A11 ,A12 ,A21, A22;
		M B11 ,B12 ,B21, B22;
		M C11 ,C12 ,C21, C22;
		M M1, M2 ,M3, M4, M5, M6, M7; 
		M AA , BB;
		A11.size=n/2;	A12.size=n/2;	A21.size=n/2;	A22.size=n/2;
		B11.size=n/2;	B12.size=n/2;	B21.size=n/2;	B22.size=n/2;
		M1.size=n/2;	M2.size=n/2; M3.size=n/2; M4.size=n/2; M5.size=n/2; M6.size=n/2; M7.size=n/2;
		AA.size=n/2;	BB.size=n/2;

		//Matrix seprated to four Matrix
		int i,j;
		//#pragma omp parallGel for private(j)
		for(i=0; i<n/2; i++){
			for(j=0; j<n/2; j++){
				A11.MX[i][j]=A.MX[i][j];
				A12.MX[i][j]=A.MX[i][j+n/2];
				A21.MX[i][j]=A.MX[i+n/2][j];
				A22.MX[i][j]=A.MX[i+n/2][j+n/2];
				
				B11.MX[i][j]=B.MX[i][j];
				B12.MX[i][j]=B.MX[i][j+n/2];
				B21.MX[i][j]=B.MX[i+n/2][j];
				B22.MX[i][j]=B.MX[i+n/2][j+n/2];
			}
		}
		
		
		//#pragma omp parallel sections
		{
		//	#pragma omp section
			{
				//M1 = (A11+A22)(B11+B22);
				AA = A11+A22;
				BB = B11+B22;
				Strassen(n/2, AA, BB ,M1);
			}
		//	#pragma omp section
			{
				//M2 = (A21+A22)*B11;
				AA = A21+A22; 
				Strassen(n/2, AA, B11, M2);
			}
		//	#pragma omp section
			{
				//M3 = A11*(B12-B22);
				BB = B12-B22;
				Strassen(n/2, A11, BB, M3);
			}
		//	#pragma omp section
			{
				//M4 = A22*(B21-B11);
				BB = B21-B11;
				Strassen(n/2, A22, BB, M4);
			}
		//	#pragma omp section
			{
				//M5 = (A11+A12)*B22;
				AA = A11+A12;
				Strassen(n/2, AA, B22, M5);
			}
		//	#pragma omp section
			{
				//M6 = (A21-A11)*(B11+B12);
				AA = A21-A11;
				BB = B11+B12;
				Strassen(n/2, AA, BB, M6);
			}
		//	#pragma omp section
			{
				//M7 = (A12-A22)*(B21+B22);	
				AA = A12-A22;
				BB = B21+B22;
				Strassen(n/2, AA, BB, M7);
			}
		}

		//#pragma omp parallel sections
		{
		//	#pragma omp section
			{
				C11 = M1+M4-M5+M7;
				//std::cout<<C11;
				C12 = M3+M5;
				//std::cout <<C12;
				C21 = M2+M4;
				//std::cout <<C21;
				C22 = M1+M3-M2+M6;
				//std::cout <<C22;
			}
		}
		
		//#pragma omp parallel for private(j)
		for(i=0; i<n/2; i++){
			for(j=0; j<n/2; j++){
				C.MX[i][j] = C11.MX[i][j];
				C.MX[i][j+n/2] = C12.MX[i][j];
				C.MX[i+n/2][j] = C21.MX[i][j];
				C.MX[i+n/2][j+n/2] = C22.MX[i][j];

			}
		}
	}
}





int main(){
	struct timespec t_start, t_end;
	double elapsedTime;
	int i, j, k;
	int temp;
	M A,B,CS,C,BS;
	for( i=0; i<N; i++ ){
		for( j=0; j<N; j++ ) {
			A.MX[i][j] = rand()%10;
			B.MX[i][j] = rand()%10;
		}
	}
	BS=B;
	//std::cout <<A<<"\n"<<B;

	clock_gettime( CLOCK_REALTIME, &t_start);
   	//transpose of b
	for( i=0; i<N; i++ ){
		for( j=i+1; j<N; j++ ) {
			temp = BS.MX[j][i];
			BS.MX[j][i] = BS.MX[i][j];
			BS.MX[i][j] = temp;
		}
	}
	for( i=0; i<N; i++ ){
		for( j=0; j<N; j++ ) {
			CS.MX[i][j] = 0;
			for( k=0; k<N; k++ ){
				CS.MX[i][j] += A.MX[i][k]*BS.MX[j][k];
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

	/*Strassen*/
	clock_gettime( CLOCK_REALTIME, &t_start);
	Strassen(N,A,B,C);

	// stop time
	clock_gettime( CLOCK_REALTIME, &t_end);
	// compute and print the elapsed time in millisec
	elapsedTime = (t_end.tv_sec - t_start.tv_sec) * 1000.0;
	elapsedTime += (t_end.tv_nsec - t_start.tv_nsec) / 1000000.0;
	printf("Strassen elapsedTime: %lf ms\n", elapsedTime);

	//std::cout<<CS<<"\n"<<C;
	//Test Pass
	bool Ferror=false;
	for(int i = 0; i <N; i++){
		for(j=0; j<N; j++ ) {
			if(C.MX[i][j]!=CS.MX[i][j]){
				Ferror=true;
				break;
			}
		}
		if(Ferror==true)
			break;
	}
	if(Ferror==true)
		std::cout<<"Error\n";
	else
		std::cout<<"True\n";
   return 0;
}

