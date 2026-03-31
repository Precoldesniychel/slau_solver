#include "matrix_utils.h"
#include <cmath>
#include <iostream>
#include <iomanip>

std::vector<std::vector<double>> generateRandomMatrix(int n, int seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = dis(gen);
    return A;
}

std::vector<double> generateRandomVector(int n, int seed) {
    std::mt19937 gen(seed + 1);
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    std::vector<double> b(n);
    for (int i = 0; i < n; ++i)
        b[i] = dis(gen);
    return b;
}

std::vector<std::vector<double>> generateHilbertMatrix(int n) {
    std::vector<std::vector<double>> H(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            H[i][j] = 1.0 / (double)(i + j + 1);
    return H;
}

std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    int n = A.size();
    std::vector<double> res(n, 0.0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            res[i] += A[i][j] * x[j];
    return res;
}

double norm(const std::vector<double>& v) {
    double sum = 0.0;
    for (double x : v) sum += x * x;
    return std::sqrt(sum);
}

std::vector<double> subtractVectors(const std::vector<double>& a, const std::vector<double>& b) {
    int n = a.size();
    std::vector<double> res(n);
    for (int i = 0; i < n; ++i) res[i] = a[i] - b[i];
    return res;
}

std::vector<std::vector<double>> copyMatrix(const std::vector<std::vector<double>>& A) {
    int n = A.size();
    std::vector<std::vector<double>> B(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            B[i][j] = A[i][j];
    return B;
}


std::vector<double> copyVector(const std::vector<double>& v) {
    return v;
}

void printMatrix(const std::vector<std::vector<double>>& A, int maxDisplay) {
    int n = A.size();
    int displaySize = (n <= maxDisplay) ? n : maxDisplay;
    
    std::cout << "    [";
    for (int i = 0; i < displaySize; ++i) {
        if (i > 0) std::cout << "     ";
        std::cout << "[";
        for (int j = 0; j < displaySize; ++j) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << A[i][j];
            if (j < displaySize - 1) std::cout << ", ";
        }
        if (n > maxDisplay) std::cout << ", ...";
        std::cout << "]";
        if (i < displaySize - 1) std::cout << "," << std::endl;
    }
    if (n > maxDisplay) {
        std::cout << "     ... (" << (n - maxDisplay) << " more rows)]" << std::endl;
    } else {
        std::cout << "    ]" << std::endl;
    }
}

void printVector(const std::vector<double>& v, int maxDisplay) {
    int n = v.size();
    int displaySize = (n <= maxDisplay) ? n : maxDisplay;
    
    std::cout << "    [";
    for (int i = 0; i < displaySize; ++i) {
        std::cout << std::setw(10) << std::fixed << std::setprecision(4) << v[i];
        if (i < displaySize - 1) std::cout << ", ";
    }
    if (n > maxDisplay) std::cout << ", ...";
    std::cout << "]" << std::endl;
}