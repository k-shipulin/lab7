#pragma once
#include "MatSize.h"

class SimpleMatOperations 
{
public:
	virtual  void getI(float* I);

	virtual void trans(float* mat, float* res);

	virtual void div(float* mat, float v);

	virtual float maxI(float* A);

	virtual float maxJ(float* A);

	virtual void mul(float* A, float* B, float* C);

	virtual void inverseMat(float* A, float* BB, float* R, float* R1, float* R2, float* I);

	virtual void add(float* a, float* b);

	virtual void sub(float* A, float* B, float* R);
protected:
	float abs(float a);
};