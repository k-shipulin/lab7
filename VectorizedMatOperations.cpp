#include "VectorizedMatOperations.h"

void VectorizedMatOperations::getI(float* I) {
	for (int i = 0; i < N2; i += N)
		for (int j = 0; j < N; j += 4)
			_mm_storeu_ps(I + i + j, _mm_setzero_ps());
	for (int i = 0; i < N; i++)
		I[i * N + i] = 1;
}

void VectorizedMatOperations::div(float* mat, float v) {
	__m128 divider = _mm_set1_ps(v);
	for (int iN = 0; iN < N2; iN += N)
		for (int j = 0; j < N; j += 4) {
			float* dist = mat + iN + j;
			_mm_storeu_ps(dist, _mm_div_ps(_mm_loadu_ps(dist), _mm_set1_ps(v)));
		}
}

float VectorizedMatOperations::maxJ(float* A) {
	float s[N];
	for (int i = 0; i < N; i += 4) {
		_mm_storeu_ps(s + i, _mm_setzero_ps());
	}
	for (int i = 0; i < N2; i += N) {
		const float* a = A + i;
		for (int j = 0; j < N; j += 4)
			_mm_storeu_ps(s + j, _mm_add_ps(
				_mm_loadu_ps(s + j), _mm_loadu_ps(a + j)));
	}
	float max = 0;
	for (int i = 0; i < N; i += 4) {
		s[i] = abs(s[i]);
		max = (max < s[i] ? s[i] : max);
	}
	return max;
}

void VectorizedMatOperations::mul(float* A, float* B, float* C) {


	for (int i = 0; i < N; ++i) {
		float* c = C + i * N;
		for (int j = 0; j < N; j += 4)
			_mm_storeu_ps(c + j, _mm_setzero_ps());
		for (int k = 0; k < N; ++k) {
			const float* b = B + k * N;
			//float a = A[i*N + k];
			__m128 a = _mm_set1_ps(A[i * N + k]);

			for (int j = 0; j < N; j += 4) {
				_mm_storeu_ps(c + j, _mm_add_ps(_mm_mul_ps(a,
					_mm_loadu_ps(b + j)), _mm_loadu_ps(c + j)));
			}
		}
	}
}

void VectorizedMatOperations::add(float* A, float* B) {
	for (int i = 0; i < N2; i += N) {
		float* a = A + i;
		float* b = B + i;
		for (int j = 0; j < N; j += 4)
			_mm_storeu_ps(a + j, _mm_add_ps(
				_mm_loadu_ps(b + j), _mm_loadu_ps(a + j)));
	}
}

void VectorizedMatOperations::sub(float* A, float* B, float* R) {
	for (int i = 0; i < N2; i += N) {
		float* a = A + i;
		float* b = B + i;
		float* r = R + i;
		for (int j = 0; j < N; j += 4)
			_mm_storeu_ps(r + j, _mm_sub_ps(
				_mm_loadu_ps(a + j), _mm_loadu_ps(b + j)));
	}
}