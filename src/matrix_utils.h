#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>
#include <random>

std::vector<std::vector<double>> generateRandomMatrix(int n, int seed);
std::vector<double> generateRandomVector(int n, int seed);
std::vector<std::vector<double>> generateHilbertMatrix(int n);
std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& A, const std::vector<double>& x);
double norm(const std::vector<double>& v);
std::vector<double> subtractVectors(const std::vector<double>& a, const std::vector<double>& b);
std::vector<std::vector<double>> copyMatrix(const std::vector<std::vector<double>>& A);
std::vector<double> copyVector(const std::vector<double>& v);


void printMatrix(const std::vector<std::vector<double>>& A, int maxDisplay = 5);
void printVector(const std::vector<double>& v, int maxDisplay = 10);

#endif