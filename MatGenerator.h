#pragma once

#include "MatSize.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

class MatrixIO {
public:
	static void generateMatrix(const std::string& fileName);

	static void generateMatrix(float* A);

	static int readMatrix(float* mat, const std::string& fileName);

	static void writeMatrix(float* mat, const std::string& fileName);

	static void writeMatrix(float* mat);

	static void writeMatrix(float* mat, std::ostream& stream);

private:
	static float getRandFloat();
};