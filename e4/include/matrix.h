#ifndef _MATRIX_H_
#define _MATRIX_H_  
#include <memory>
#include <iostream>
 
/// 矩阵
struct Matrix
{
private:
    int rowc;
    int colc;
    std::shared_ptr<int[]> buff;

public:

    enum class InitMethod
    {
        Identity, Zero, Random, One
    };

    /// 创建空矩阵
    Matrix();

    /// 初始化r行c列的矩阵
    Matrix(int r, int c, InitMethod method = InitMethod::Random);

    /// 返回r行c列的元素
    int& operator()(int r, int c);

    /// 返回r行c列的元素
    const int& operator()(int r, int c) const;

    /// 行数
    int col() const;

    /// 列数
    int row() const;

    /// 矩阵乘
    Matrix operator*(const Matrix& b);

    /// 矩阵加
    Matrix operator+(const Matrix& b);

    int* begin();

    int* end();

    const int* begin() const;

    const int* end() const;

    friend std::ostream& operator<<(std::ostream& s, const Matrix& mat);
    
    friend std::istream& operator>>(std::istream& s, Matrix& mat);
};

std::ostream& operator<<(std::ostream& s, const Matrix& mat);

std::istream& operator>>(std::istream& s, Matrix& mat);


#endif // _MATRIX_H_