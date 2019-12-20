#include "BLASMatOperations.h"
#include "MatGenerator.h"

namespace {
	float II[N2];
}

void BLASMatOperations::inverseMat(float* A, float* BB, float* R, float* R1, float* R2, float* I) {
	float* K[2] = { R1, R2 };

	this->getI(I);


	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
		N, N, N,
		1 / (this->maxI(A) * this->maxJ(A)), A, N,
		II, N,
		0.0, BB, N);


	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N,
		1.0, BB, N,
		A, N,
		0.0, R, N);

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N,
		1.0, I, N,
		I, N,
		-1.0, R, N);


	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N,
		1.0, R, N,
		II, N,
		1.0, I, N);

	bool w = false;

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N,
		1.0, R, N,
		R, N,
		0, K[w], N);

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N,
		1.0, K[w], N,
		II, N,
		1.0, I, N);

	for (int i = 2; i < M; i++) {
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, N, N,
			1.0, K[w], N,
			R, N,
			0, K[!w], N);

		w = !w;

		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			N, N, N,
			1.0, K[w], N,
			II, N,
			1, I, N);

	}



	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		N, N, N,
		1.0, I, N,
		BB, N,
		0, R, N);
}

BLASMatOperations::BLASMatOperations() {
	this->getI(II);
}
