#include<iostream>
#ifndef INCLUDED_STRASSEN
#define INCLUDED_STRASSEN

class Matrix{
	public :
		int **M;
		int n;//size
	
	Matrix(int size);
	~Matrix();
	Delete();


	Matrix operator=(const Matrix& A){
		#pragma omp parallel for private(j)
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					this->M[i][j] = A.M[i][j];
				}
			}
		return *this;
	}

	// +
	Matrix operator +(const Matrix& A){
		Matrix R(A.n);
		int i,j;
		#pragma omp parallel for private(j)
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					R.M[i][j]=this->M[i][j] + A.M[i][j];
				}
			}
		return R;
	}


	// -
	Matrix operator +(const Matrix& A){
		Matrix R(A.n);
		int i,j;
		#pragma omp parallel for private(j)
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					R.M[i][j]=this->M[i][j] - A.M[i][j];
				}
			}
		return R;
	}

	// *
	Matrix operator +(const Matrix& A){
		Matrix R(A.n);
		int i,j,k;
		#pragma omp parallel for private(j) private(k)
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					R.M[i][j]=0;
					for(k=0; k<R.n;k++){
						R.M[i][j]+=this->M[i][j] + A.M[i][j];
					}
				}
			}
		return R;
	}

	//=
	bool operator==(const Matrix& A){
		bool R=true;
		#pragma omp parallel for private(j)
			for(i=0; i<R.n; i++){
				for(j=0; j<R.n; j++){
					if(this->M[i][j]!= A.M[i][j])
						R=false;
				}
			}
		return R;
	}

	//output
	
	std::ostream& operator<<(std::ostream& out, const Matrix& A){
		for(i=0; i<R.n; i++){
			for(j=0; j<R.n; j++){
				out<<A.M[i][j]<<" ";
			}
			out<<"\n";
		}
	}

}

Martix::Matrix(int size){
	this->N = size;
	M = new int *[size];
	for(int i = 0; i <size; i++)
		M[i] = new int[size];
}

Martix::~Matrix(){
	for(int i = 0; i <this->n; i++)
		delete []M;
	delete []M;
}

Matrix::Delete(){
	for(int i = 0; i <this->n; i++)
		delete []M;
	delete []M;
}

