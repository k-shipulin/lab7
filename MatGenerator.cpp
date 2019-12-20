#include "MatGenerator.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

float MatrixIO::getRandFloat() {
	return (float)(rand() - RAND_MAX / 2) * 10 / (RAND_MAX);
}


void MatrixIO::generateMatrix(const std::string& fileName) {

	std::ofstream file;
	file.open(fileName.c_str());

	file << N << std::endl;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			file << getRandFloat() << " ";
		}
		file << std::endl;
	}
	file.close();
}

void MatrixIO::generateMatrix(float* A) {
	for (int i = 0; i < N2; i += N) {
		for (int j = 0; j < N; j++) {
			A[i + j] = getRandFloat();
		}
	}
}

int MatrixIO::readMatrix(float* mat, const std::string& fileName) {
	std::ifstream file;
	file.open(fileName.c_str());

	for (int i = 0; i < N * N; i += N) {
		for (int j = 0; j < N; j++) {
			file >> mat[i + j];
		}
	}
	file.close();
	return N;
}

void MatrixIO::writeMatrix(float* mat, const std::string& fileName) {
	std::ofstream file;
	file.open(fileName.c_str());

	writeMatrix(mat, file);
	file.close();

}

void MatrixIO::writeMatrix(float* mat) {
	writeMatrix(mat, std::cout);
}

void MatrixIO::writeMatrix(float* mat, std::ostream& stream) {
	stream << N << std::endl;

	stream << std::fixed;
	stream.precision(2);

	for (int i = 0; i < N * N; i += N) {
		for (int j = 0; j < N; j++) {
			stream.width(6);
			stream << mat[i + j] << " ";
		}
		stream << std::endl;
	}

}
