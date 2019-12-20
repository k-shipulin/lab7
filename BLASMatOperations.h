#include "MatSize.h"

#pragma once
#include "MatSize.h"
#include "VectorizedMatOperations.h"

#ifdef __INTEL_COMPILER
#include<mkl_cblas.h> // C-интерфейс BLAS (заголовочный файл из MKL)
#else
#include<cblas.h> // C-интерфейс BLAS (стандартный заголовочный файл)
#endif

class BLASMatOperations : public VectorizedMatOperations {
public:
	BLASMatOperations();
	void inverseMat(float* A, float* BB, float* R, float* R1, float* R2, float* I);

};
