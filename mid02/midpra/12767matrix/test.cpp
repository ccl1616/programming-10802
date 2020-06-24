#include <iostream>
#include <cstdlib>
#include "function.h"
using namespace std;

Matrix::~Matrix()
{
    for(int i = 0; i < n; i ++)
        delete[] matrix[i];
    delete matrix;
}

Matrix::Matrix(int n)
    :n(n)
{
    matrix = new long long* [n];
    for(int i = 0; i < n; i ++){
        matrix[i] = new long long[n];
        for(int j = 0; j < n; j ++)
            matrix[i][j] = 0;
    }
}

// copy constructor
Matrix::Matrix(const Matrix& ref)
    :n(ref.n)
{
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++)
            matrix[i][j] = ref(i,j);
    }
}

Matrix& Matrix::operator=(const Matrix& ref)
{
    this->n = ref.n;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++)
            matrix[i][j] = ref(i,j);
    }
    return *this;
}

long long& Matrix::operator()(const int& row, const int& column) const
{
    return matrix[row][column];
}

void Matrix::toIdentity()
{
    for(int i =0; i < n; i ++)
        matrix[i][i] = 1;
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
    Matrix ans(n);

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            for(int k = 0; k < n; k ++){
                ans(i,j) += this->matrix[i][k] * rhs(k,j);
                ans(i,j) = ans(i,j) % mod;
            }
        }
    }
    return ans;
}

Matrix Matrix::power(int k) const
{
    Matrix init(n);
    init.toIdentity();
    Matrix ret(n);
    ret = *this;

    while(k > 0){
        if(k % 2) init = init * ret;
        ret = ret * ret;
        k /= 2;
    }
    return init;
}

Matrix constructMatrix(int n)
{   
    Matrix ret(n);
    for(int i = 0; i < n-1; i ++)
        ret(i,i+1) = 1;
    for(int i = 0; i < n; i ++)
        ret(n-1,i) = 1;
    return ret;
}