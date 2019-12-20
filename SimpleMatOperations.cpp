#include "SimpleMatOperations.h"
#include "MatGenerator.h"

void SimpleMatOperations::getI(float* I) {
	for (int i = 0; i < N2; i += N)
		for (int j = 0; j < N; j++)
			I[i + j] = 0;
	for (int i = 0; i < N; i++)
		I[i * N + i] = 1;
}

void SimpleMatOperations::trans(float* mat, float* res) {
	for (int i = 0, iN = 0; i < N; i++, iN += N)
		for (int j = 0, jN = 0; j < N; j++, jN += N)
			res[iN + j] = mat[i + jN];
}

void SimpleMatOperations::div(float* mat, float v) {
	for (int iN = 0; iN < N2; iN += N)
		for (int j = 0; j < N; j++)
			mat[iN + j] /= v;
}

float SimpleMatOperations::maxI(float* A) {
	float max = 0;
	for (int i = 0; i < N2; i += N) {
		float s = 0;
		const float* a = A + i;
		for (int j = 0; j < N; j++)
			s += a[j];
		s = abs(s);
		max = (max < s ? s : max);
	}
	return max;
}

float SimpleMatOperations::maxJ(float* A) {
	float s[N];
	for (int i = 0; i < N; i++) {
		s[i] = 0;
	}
	for (int i = 0; i < N2; i += N) {
		const float* a = A + i;
		for (int j = 0; j < N; j++)
			s[j] += a[j];
	}
	float max = 0;
	for (int i = 0; i < N; i++) {
		s[i] = abs(s[i]);
		max = (max < s[i] ? s[i] : max);
	}
	return max;
}

void SimpleMatOperations::mul(float* A, float* B, float* C) {
	for (int i = 0; i < N; ++i) {
		float* c = C + i * N;
		for (int j = 0; j < N; ++j)
			c[j] = 0;
		for (int k = 0; k < N; ++k) {
			const float* b = B + k * N;
			float a = A[i * N + k];
			for (int j = 0; j < N; ++j)
				c[j] += a * b[j];
		}
	}
}

void SimpleMatOperations::add(float* a, float* b) {
	for (int iN = 0; iN < N2; iN += N)
		for (int j = 0; j < N; j++)
			a[iN + j] += b[iN + j];
}

void SimpleMatOperations::sub(float* A, float* B, float* R) {
	for (int iN = 0; iN < N2; iN += N) {
		float* a = A + iN;
		float* b = B + iN;
		float* r = R + iN;
		for (int j = 0; j < N; j++) {
			r[j] = a[j] - b[j];
		}
	}
}

float SimpleMatOperations::abs(float x) {
	return (x < 0 ? -x : x);
}

void SimpleMatOperations::inverseMat(float* A, float* BB, float* R, float* R1, float* R2, float* I) {
	float* K[2] = { R1, R2 };

	this->getI(I);
	this->trans(A, BB);
	this->div(BB, this->maxI(A) * this->maxJ(A));

	this->mul(BB, A, R);

	this->sub(I, R, R);

	this->add(I, R);

	bool w = false;
	this->mul(R, R, K[w]);
	this->add(I, K[w]);

	for (int i = 2; i < M; i++) {
		this->mul(K[w], R, K[!w]);
		w = !w;
		this->add(I, K[w]);
	}

	this->mul(I, BB, R);
}