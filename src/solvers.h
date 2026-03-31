#ifndef SOLVERS_H
#define SOLVERS_H

#include <vector>

void gaussianEliminationNoPivot(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>& x);
void gaussianEliminationPartialPivot(std::vector<std::vector<double>> A, std::vector<double> b, std::vector<double>& x);
void luDecomposition(const std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U);
void forwardSubstitution(const std::vector<std::vector<double>>& L, const std::vector<double>& b, std::vector<double>& y);
void backwardSubstitution(const std::vector<std::vector<double>>& U, const std::vector<double>& y, std::vector<double>& x);
void solveWithLU(const std::vector<std::vector<double>>& L, const std::vector<std::vector<double>>& U, const std::vector<double>& b, std::vector<double>& x);

#endif