#pragma once

#include <immintrin.h>
#include "MatSize.h"
#include "SimpleMatOperations.h"

class VectorizedMatOperations : public SimpleMatOperations {
public:
	virtual void getI(float* I);

	virtual void div(float* mat, float v);

	virtual float maxJ(float* A);

	virtual void mul(float* A, float* B, float* C);

	virtual void add(float* a, float* b);

	virtual void sub(float* A, float* B, float* R);

};