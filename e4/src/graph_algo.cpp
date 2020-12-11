#include "graph_algo.h"

Matrix accessibility_matrix(const Matrix& mat)
{
    if (mat.row() != mat.col()) throw "need a sqaure matrix";
    const int n = mat.row();
    Matrix lastterm(n, n, Matrix::InitMethod::Identity);
    Matrix res(n, n, Matrix::InitMethod::Identity);
    for (int i = 0; i < n; i++) {
        lastterm = lastterm * mat;
        res = res + lastterm;
    }
    for (auto&& i : res) {
        i = i != 0;
    }
    return res;
}