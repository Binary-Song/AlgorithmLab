#include "matrix.h"
#include <stdlib.h>


/// 创建空矩阵
Matrix::Matrix() :rowc(0), colc(0), buff(nullptr) {}

/// 初始化r行c列的矩阵
Matrix::Matrix(int r, int c, InitMethod method) : rowc(r), colc(c), buff(new int[r * c])
{
    switch (method) {
    case InitMethod::Identity:
        for (int i = 0;i < r;i++) {
            for (int j = 0;j < c;j++) {
                (*this)(i, j) = i == j;
            }
        }
        break;
    case InitMethod::Random:
        for (auto&& e : *this) {
            e = rand() % 100 < 10;
        }
        break;
    case InitMethod::Zero:
        for (auto&& e : *this) {
            e = 0;
        }
        break;
    case InitMethod::One:
        for (auto&& e : *this) {
            e = 1;
        }
        break;
    }
}

/// 返回r行c列的元素
int& Matrix::operator()(int r, int c)
{
#ifndef NDEBUG
    if (r >= rowc || c >= colc || r < 0 || c < 0) throw "index out of bounds";
#endif
    return buff[r * colc + c];
}

/// 返回r行c列的元素
const int& Matrix::operator()(int r, int c) const
{
#ifndef NDEBUG
    if (r >= rowc || c >= colc || r < 0 || c < 0) throw "index out of bounds";
#endif
    return buff[r * colc + c];
}

int Matrix::col() const { return colc; }

int Matrix::row() const { return rowc; }

Matrix Matrix::operator*(const Matrix& b)
{
    Matrix& a = *this;
    if (a.colc != b.rowc) throw "cannot multiply, sizes disagree";
    Matrix p(a.rowc, b.colc);
    for (int ri = 0;ri < p.rowc;ri++) {
        for (int ci = 0; ci < p.colc; ci++) {
            int comb = 0;
            for (int k = 0; k < a.colc; k++) {
                comb += a(ri, k) * b(k, ci);
            }
            p(ri, ci) = comb;
        }
    }
    return p;
}

Matrix Matrix::operator+(const Matrix& b)
{
    Matrix& a = *this;
    if (a.colc != b.colc || a.rowc != b.rowc) throw "cannot add, sizes disagree";
    Matrix s(rowc, colc);
    for (int ri = 0;ri < s.rowc;ri++) {
        for (int ci = 0; ci < s.colc; ci++) {
            s(ri, ci) = a(ri, ci) + b(ri, ci);
        }
    }
    return s;
}

std::ostream& operator<<(std::ostream& s, const Matrix& mat)
{
    for (int ri = 0; ri < mat.rowc; ri++) {

        for (int ci = 0; ci < mat.colc; ci++) {
            if (ci == 0) {
                s << "  " << mat(ri, ci);
            }
            else {
                s << ", " << mat(ri, ci);
            }
        }
        s << "\n";
    }
    return s;
}


std::istream& operator>>(std::istream& s, Matrix& mat)
{
    for (int ri = 0; ri < mat.rowc; ri++) {
        for (int ci = 0; ci < mat.colc; ci++) {
            s >> mat(ri, ci);
        }
    }
    return s;
}

int* Matrix::begin()
{
    return buff.get();
}

int* Matrix::end()
{
    return buff.get() + rowc * colc;
}

const int* Matrix::begin() const
{
    return buff.get();
}

const int* Matrix::end() const
{
    return buff.get() + rowc * colc;
}
