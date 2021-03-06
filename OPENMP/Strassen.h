#include<stdio.h>
#include<iostream>
#include<omp.h>
#include<algorithm>
#define T 16
//#ifndef INCLUDED_STRASSEN
//#define INCLUDED_STRASSEN

class Matrix{
	public :
		int **M;
		int n;//size

	Matrix(){
		this->n = 0;
	}
	Matrix(int size){
		this->n = size;
		M = new int* [size];
		for(int i = 0; i <size; i++)
			M[i] = new int[size];
	}
	~Matrix(){
		for(int i = 0; i <n; i++)
			delete[] this->M[i];
		delete[] this->M;
	}
	void Delete(){
		for(int i = 0; i <n; i++)
			delete[] this->M[i];
		delete[] this->M;
	}
	
	Matrix operator=(const Matrix& A){
		int i,j;
		Matrix R(A.n);
		R.n=A.n;
		#pragma omp parallel for private(j) schedule(static, T)
		//#pragma omp parallel for private(j) 
			for(i=0;i<A.n; i++){
				for(j=0;j<A.n; j++){
					R.M[i][j] = A.M[i][j];
					M[i][j]=A.M[i][j];
				}
			}
	//	std::cout<<"\n"<<R<<"\n";
		
		return R;
	}

	// +
	Matrix operator+(const Matrix& A){
		Matrix R(A.n);
		int i,j;
		#pragma omp parallel for private(j) schedule(static,T)
		//#pragma omp parallel for private(j) 
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					R.M[i][j]=M[i][j] + A.M[i][j];
				}
			}
		return R;
	}


	// -
	Matrix operator-(const Matrix& A){
		Matrix R(A.n);
		int i,j;
		#pragma omp parallel for private(j) schedule(static, T)
		//#pragma omp parallel for private(j) 
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					R.M[i][j]=M[i][j] - A.M[i][j];
				}
			}
		return R;
	}

	// *
	Matrix operator*(const Matrix& A){
		Matrix R(A.n);
		Matrix At(A.n);
		At=A;
		int i,j,k;

		//transpose
		#pragma omp parallel for private(j) schedule(static, T)
		//#pragma omp parallel for private(j) 
		for( i=0; i<R.n; i++ ){
			for( j=i; j<R.n; j++ ) {
				std::swap(At.M[i][j], At.M[j][i]);
			}
		}

		//std::cout<<A<<"\n"<<At<<"\n";

		#pragma omp parallel for private(j) private(k) schedule(static, T)
		//#pragma omp parallel for private(j) private(k) 
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					R.M[i][j]=0;
					for(k=0; k<R.n;k++){
						R.M[i][j]+=M[i][k] * At.M[j][k];
					}
				}
			}
		return R;
	}

	//=
	bool operator==(const Matrix& A){
		bool R=true;
		int i,j;
			for(i=0; i<n; i++){
				for(j=0; j<n; j++){
					if(M[i][j]!= A.M[i][j])
						R=false;
				}
			}
		return R;
	}

	//output
	
	friend std::ostream& operator<<(std::ostream& out,const Matrix& A){
		int i,j;
//		std::cout<<"1\n";
		for(i=0; i<A.n; i++){
			for(j=0; j<A.n; j++){
				out<<A.M[i][j]<<" ";
			}
			out<<"\n";
		}
//		std::cout<<"2\n";
		return out;
	}
};
