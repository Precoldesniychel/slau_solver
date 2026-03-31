#include "experiments.h"
#include "matrix_utils.h"
#include "solvers.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

double measureTimeGaussNoPivot(const vector<vector<double>>& A, const vector<double>& b) {
    auto start = high_resolution_clock::now();
    vector<double> x;
    gaussianEliminationNoPivot(copyMatrix(A), copyVector(b), x);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

double measureTimeGaussPivot(const vector<vector<double>>& A, const vector<double>& b) {
    auto start = high_resolution_clock::now();
    vector<double> x;
    gaussianEliminationPartialPivot(copyMatrix(A), copyVector(b), x);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

pair<double, double> measureTimeLU(const vector<vector<double>>& A, const vector<double>& b) {
    auto startDecomp = high_resolution_clock::now();
    vector<vector<double>> L, U;
    luDecomposition(A, L, U);
    auto endDecomp = high_resolution_clock::now();
    double decompTime = duration<double, milli>(endDecomp - startDecomp).count();

    auto startSolve = high_resolution_clock::now();
    vector<double> x;
    solveWithLU(L, U, b, x);
    auto endSolve = high_resolution_clock::now();
    double solveTime = duration<double, milli>(endSolve - startSolve).count();

    return {decompTime, solveTime};
}

void experiments::runExperiment4_1(bool verbose) {
    cout << "\n=== Experiment 4.1: Single System Solution Time ===\n";
    
    vector<int> sizes = {100, 200, 500, 1000};
    int seed = 42;

    if (verbose) {
        cout << "\n[Sample] Random Matrix A (n=100, seed=42) - first 5x5 elements:\n";
        auto A_sample = generateRandomMatrix(100, seed);
        printMatrix(A_sample, 5);
        cout << "[Sample] Random Vector b (n=100, seed=42) - first 10 elements:\n";
        auto b_sample = generateRandomVector(100, seed);
        printVector(b_sample, 10);
        cout << endl;
    }

    cout << left << setw(10) << "N" << setw(15) << "Gauss No Pivot" 
         << setw(15) << "Gauss Pivot" << setw(15) << "LU Decomp" 
         << setw(15) << "LU Solve" << setw(15) << "LU Total" << endl;
    cout << string(85, '-') << endl;

    for (int n : sizes) {
        auto A = generateRandomMatrix(n, seed);
        auto b = generateRandomVector(n, seed);

        double t1 = measureTimeGaussNoPivot(A, b);
        double t2 = measureTimeGaussPivot(A, b);
        auto [t3, t4] = measureTimeLU(A, b);
        double t5 = t3 + t4;

        cout << left << setw(10) << n 
             << setw(15) << fixed << setprecision(2) << t1 
             << setw(15) << t2 
             << setw(15) << t3 
             << setw(15) << t4 
             << setw(15) << t5 << endl;
    }
}

void experiments::runExperiment4_2(bool verbose) {
    cout << "\n=== Experiment 4.2: Multiple Right-Hand Sides (N=500) ===\n";
    int n = 500;
    int seed = 42;
    auto A = generateRandomMatrix(n, seed);
    vector<int> ks = {1, 10, 100};

    if (verbose) {
        cout << "\n[Sample] Matrix A (n=500, seed=42) - first 5x5 elements:\n";
        printMatrix(A, 5);
        
        cout << "\n[Sample] First 3 right-hand side vectors (first 10 elements each):\n";
        for (int i = 0; i < 3; ++i) {
            auto b = generateRandomVector(n, seed + i);
            cout << "  b[" << i << "] (seed=" << (seed + i) << "): ";
            printVector(b, 10);
        }
        cout << endl;
    }

    cout << left << setw(10) << "K" << setw(20) << "Gauss Pivot Total" 
         << setw(25) << "LU Total (1 Decomp + K Solves)" << endl;
    cout << string(60, '-') << endl;

    for (int k : ks) {
        double timeGauss = 0.0;
        for (int i = 0; i < k; ++i) {
            auto b = generateRandomVector(n, seed + i);
            timeGauss += measureTimeGaussPivot(A, b);
        }

        auto b0 = generateRandomVector(n, seed);
        auto [tDecomp, tSolveOne] = measureTimeLU(A, b0);
        double timeLU = tDecomp + k * tSolveOne;

        cout << left << setw(10) << k 
             << setw(20) << fixed << setprecision(2) << timeGauss 
             << setw(25) << timeLU << endl;
    }
}

void experiments::runExperiment4_3(bool verbose) {
    cout << "\n=== Experiment 4.3: Accuracy on Hilbert Matrices ===\n";
    vector<int> sizes = {5, 10, 15};
    
    if (verbose) {
        cout << "\n[Sample] Hilbert Matrix H (n=5) - full matrix:\n";
        auto H_sample = generateHilbertMatrix(5);
        printMatrix(H_sample, 5);
        
        cout << "\n[Sample] Exact solution x = (1, 1, ..., 1)^T, n=5:\n";
        vector<double> xExact_sample(5, 1.0);
        printVector(xExact_sample, 10);
        
        cout << "\n[Sample] Computed right-hand side b = H*x (n=5):\n";
        auto b_sample = multiplyMatrixVector(H_sample, xExact_sample);
        printVector(b_sample, 10);
        cout << endl;
    }

    cout << left << setw(6) << "N" << setw(10) << "Method" 
         << setw(18) << "Rel Error" << setw(18) << "Residual" << endl;
    cout << string(52, '-') << endl;

    for (int n : sizes) {
        auto H = generateHilbertMatrix(n);
        vector<double> xExact(n, 1.0);
        auto b = multiplyMatrixVector(H, xExact);

        vector<double> xNoPivot, xPivot, xLU;
        
        gaussianEliminationNoPivot(copyMatrix(H), copyVector(b), xNoPivot);
        gaussianEliminationPartialPivot(copyMatrix(H), copyVector(b), xPivot);
        
        vector<vector<double>> L, U;
        luDecomposition(H, L, U);
        solveWithLU(L, U, b, xLU);

        auto errNoPivot = norm(subtractVectors(xNoPivot, xExact)) / norm(xExact);
        auto resNoPivot = norm(subtractVectors(multiplyMatrixVector(H, xNoPivot), b));

        auto errPivot = norm(subtractVectors(xPivot, xExact)) / norm(xExact);
        auto resPivot = norm(subtractVectors(multiplyMatrixVector(H, xPivot), b));

        auto errLU = norm(subtractVectors(xLU, xExact)) / norm(xExact);
        auto resLU = norm(subtractVectors(multiplyMatrixVector(H, xLU), b));

        cout << left << setw(6) << n << setw(10) << "Gauss NP" 
             << setw(18) << scientific << setprecision(4) << errNoPivot 
             << setw(18) << resNoPivot << endl;
        cout << left << setw(6) << n << setw(10) << "Gauss P" 
             << setw(18) << errPivot 
             << setw(18) << resPivot << endl;
        cout << left << setw(6) << n << setw(10) << "LU" 
             << setw(18) << errLU 
             << setw(18) << resLU << endl;
        cout << string(52, '-') << endl;
    }
}

void experiments::runExperiment4_4(bool verbose) {
    cout << "\n=== Experiment 4.4: Pre-computed Base vs New Right-Hand Side ===\n";
    cout << "Demonstrating advantage when LU decomposition is already computed\n";
    
    int n = 500;
    int seed = 42;
    auto A = generateRandomMatrix(n, seed);
    vector<int> ks = {1, 5, 10, 50, 100};

    if (verbose) {
        cout << "\n[Sample] Matrix A (n=" << n << ", seed=" << seed << ") - first 5x5 elements:\n";
        printMatrix(A, 5);
        cout << endl;
    }

    cout << "\n" << left << setw(8) << "K" 
         << setw(20) << "Gauss (full)" 
         << setw(20) << "LU (solve only)" 
         << setw(20) << "Speedup" << endl;
    cout << string(68, '-') << endl;

    cout << "\n[INFO] Pre-computing LU decomposition (one time)..." << endl;
    vector<vector<double>> L, U;
    auto startLU = high_resolution_clock::now();
    luDecomposition(A, L, U);
    auto endLU = high_resolution_clock::now();
    double luDecompTime = duration<double, milli>(endLU - startLU).count();
    cout << "[INFO] LU decomposition time: " << fixed << setprecision(2) << luDecompTime << " ms\n" << endl;

    for (int k : ks) {
        double timeGauss = 0.0;
        for (int i = 0; i < k; ++i) {
            auto b = generateRandomVector(n, seed + i);
            vector<double> x;
            auto start = high_resolution_clock::now();
            gaussianEliminationPartialPivot(copyMatrix(A), copyVector(b), x);
            auto end = high_resolution_clock::now();
            timeGauss += duration<double, milli>(end - start).count();
        }

        double timeLUSolve = 0.0;
        for (int i = 0; i < k; ++i) {
            auto b = generateRandomVector(n, seed + i);
            vector<double> x;
            auto start = high_resolution_clock::now();
            solveWithLU(L, U, b, x);
            auto end = high_resolution_clock::now();
            timeLUSolve += duration<double, milli>(end - start).count();
        }

        double speedup = (timeLUSolve > 0) ? timeGauss / timeLUSolve : 0;

        cout << left << setw(8) << k 
             << setw(20) << fixed << setprecision(2) << timeGauss 
             << setw(20) << timeLUSolve 
             << setw(20) << setprecision(1) << speedup << "" << endl;
    }
}