#include<iostream>
#include<omp.h>


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
		this->M = new int *[size];
		for(int i = 0; i <size; i++)
			this->M[i] = new int[size];
	}
	~Matrix(){
		for(int i = 0; i <this->n; i++)
			delete[] this->M[i];
		delete[] this->M;
	}
	void Delete(){
		for(int i = 0; i <this->n; i++)
			delete[] this->M[i];
		delete[] this->M;
	}
	
	Matrix operator=(const Matrix& A){
		int i,j;
		Matrix R(A.n);
		R.n=A.n;
//		std::cout<<"d\n";
		#pragma omp parallel for private(j)
			for(i=0;i<A.n; i++){
				for(j=0;j<A.n; j++){
//					std::cout<<A.M[i][j]<<std::endl;
					R.M[i][j] = A.M[i][j];
				}
			}
		return R;
	}

	// +
	Matrix operator+(const Matrix& A){
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
	Matrix operator-(const Matrix& A){
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
	Matrix operator*(const Matrix& A){
		Matrix R(A.n);
		Matrix At(A.n);
		int i,j,k;

		//transpose
		#pragma omp parallel for private(j)
		for( i=0; i<R.n; i++ ){
			for( j=0; j<R.n; j++ ) {
				At.M[j][i] = A.M[i][j];
			}
		}

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
		int i,j;
		#pragma omp parallel for private(j)
			for(i=0; i<this->n; i++){
				for(j=0; j<this->n; j++){
					if(this->M[i][j]!= A.M[i][j])
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
