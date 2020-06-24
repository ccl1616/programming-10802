#include <iostream>
#include <cstdlib>
#include "function.h"
using namespace std;

Matrix::~Matrix()
{
    for(int i = 0; i < n; i ++)
        delete[] matrix[i];
    delete[] matrix;
}

Matrix::Matrix(int n)
{
    
    this->n = n;
    // construct by n size
    // multiplier matrix
    matrix = new long long*[n];
    for(int i = 0; i < n; i ++){
        matrix[i] = new long long[n];
        for(int j = 0; j < n; j ++)
            matrix[i][j] = 0; //to zero
    }
    
}

// copy constructor
Matrix::Matrix(const Matrix& ref)
{
    n = ref.n;
    for(int i = 0; i < n; i ++){
        for (int j = 0; j < n; j++)
            matrix[i][j] = ref(i,j);
    }
}

// copy assignment,
Matrix& Matrix::operator=(const Matrix& ref)
{
    n = ref.n;
    // construct by n size
    for(int i = 0; i < n; i ++){
        for (int j = 0; j < n; j++)
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
    for(int i = 0; i < n; i ++)
        matrix[i][i] = 1;
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
    Matrix ans(n);
    
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){

            for(int q = 0; q < n; q++){
                // ans(i,j) += (matrix[i][q]* rhs(q,j) ) % mod ; this would be wrong
                ans(i,j) += (matrix[i][q] * rhs(q,j) ) ;
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
    ret = (*this);
    
    while(k > 0){
        if(k % 2 == 1)  init = init * ret;
        ret = ret * ret;
        k /= 2;
    }
    return init;
    
}

Matrix constructMatrix(int n)
{   
    // return a ret Matrix

    Matrix ans(n);
    // to ret
    int j = 1;
    //n-1 imp! 
    for(int i = 0; i < n-1; i ++){
        ans(i,j) = 1;
        j ++;
    }
    for(int i = 0; i < n; i ++)
        ans(n-1,i) = 1;

    return ans;
}