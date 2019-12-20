#include <iostream>
#include <string>
#include <map>
#include "time.h"

#include "MatSize.h"
#include "SimpleMatOperations.h"
#include "VectorizedMatOperations.h"
#include "BLASMatOperations.h"
#include "MatGenerator.h"


float A[N2];
float R[N2];
float R1[N2];
float R2[N2];
float BB[N2];
float I[N2];


void setZero(float* A) {
	for (int i = 0; i < N2; i += N) {
		for (int j = 0; j < N; j++) {
			A[i + j] = 0;
		}
	}
}

int main() {

	std::map<std::string, SimpleMatOperations*> operations;

	operations["Simple Operations"] = new SimpleMatOperations();
	operations["Vectorized Operations"] = new VectorizedMatOperations();
#ifdef BLAS_INSTALLED
	operations["BLAS Operations"] = new BLASMatOperations();
#endif

	clock_t start, end;
	srand(time(NULL));

	setZero(A);
#ifdef READ_MAT
	MatrixIO::readMatrix(A, "TEST.txt");
#else
	MatrixIO::generateMatrix(A);
#endif

	for (std::map<std::string, SimpleMatOperations*>::iterator op = operations.begin(); op != operations.end(); op++) {

		start = clock();
		op->second->inverseMat(A, BB, R, R1, R2, I);
		end = clock();

		end -= start;
		std::cout << op->first << " time for N = " << N << " and M = " << M << " is:" << std::endl;
		std::cout << ((float)end / CLOCKS_PER_SEC) << std::endl;

#ifdef WRITE_MAT
		op->second->mul(R, A, R1);
		MatrixIO::writeMatrix(R1, op->first + ".txt");

#endif
	}

	for (std::map<std::string, SimpleMatOperations*>::iterator op = operations.begin(); op != operations.end(); op++) {
		delete op->second;
	}
	return 0;
}
