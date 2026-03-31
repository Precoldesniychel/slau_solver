#include "solvers.h"
#include <cmath>
#include <algorithm>

const double EPS = 1e-12;

void gaussianEliminationNoPivot(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>& x) {
    int n = A.size();
    for (int k = 0; k < n; ++k) {
        if (std::abs(A[k][k]) < EPS) continue;
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; ++j)
                A[i][j] -= factor * A[k][j];
            b[i] -= factor * b[k];
        }
    }
    x.resize(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = b[i];
        for (int j = i + 1; j < n; ++j)
            sum -= A[i][j] * x[j];
        x[i] = (std::abs(A[i][i]) > EPS) ? sum / A[i][i] : 0.0;
    }
}

void gaussianEliminationPartialPivot(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>& x) {
    int n = A.size();
    for (int k = 0; k < n; ++k) {
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::abs(A[i][k]) > std::abs(A[maxRow][k]))
                maxRow = i;
        }
        if (maxRow != k) {
            std::swap(A[k], A[maxRow]);
            std::swap(b[k], b[maxRow]);
        }
        if (std::abs(A[k][k]) < EPS) continue;
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; ++j)
                A[i][j] -= factor * A[k][j];
            b[i] -= factor * b[k];
        }
    }
    x.resize(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = b[i];
        for (int j = i + 1; j < n; ++j)
            sum -= A[i][j] * x[j];
        x[i] = (std::abs(A[i][i]) > EPS) ? sum / A[i][i] : 0.0;
    }
}

void luDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    int n = A.size();
    L.assign(n, std::vector<double>(n, 0.0));
    U.assign(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int k = i; k < n; ++k) {
            double sum = 0.0;
            for (int j = 0; j < i; ++j)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }
        for (int k = i; k < n; ++k) {
            if (i == k)
                L[i][i] = 1.0;
            else {
                double sum = 0.0;
                for (int j = 0; j < i; ++j)
                    sum += L[k][j] * U[j][i];
                L[k][i] = (std::abs(U[i][i]) > EPS) ? (A[k][i] - sum) / U[i][i] : 0.0;
            }
        }
    }
}

void forwardSubstitution(const std::vector<std::vector<double>>& L, const std::vector<double>& b, std::vector<double>& y) {
    int n = L.size();
    y.resize(n);
    for (int i = 0; i < n; ++i) {
        double sum = b[i];
        for (int j = 0; j < i; ++j)
            sum -= L[i][j] * y[j];
        y[i] = sum;
    }
}

void backwardSubstitution(const std::vector<std::vector<double>>& U, const std::vector<double>& y, std::vector<double>& x) {
    int n = U.size();
    x.resize(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = y[i];
        for (int j = i + 1; j < n; ++j)
            sum -= U[i][j] * x[j];
        x[i] = (std::abs(U[i][i]) > EPS) ? sum / U[i][i] : 0.0;
    }
}

void solveWithLU(const std::vector<std::vector<double>>& L, const std::vector<std::vector<double>>& U, const std::vector<double>& b, std::vector<double>& x) {
    std::vector<double> y;
    forwardSubstitution(L, b, y);
    backwardSubstitution(U, y, x);
}