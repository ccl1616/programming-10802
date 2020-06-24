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
    int j = 1;
    for(int i = 0; i < n; i ++){
        matrix[i] = new long long[n];
    }
    for(int i = 0; i < n-1; i ++)
        matrix[i][j++] = 1;
    for(int i = 0; i < n; i ++)
        matrix[n-1][i] = 1;
}

// copy constructor
Matrix::Matrix(const Matrix& ref)
{
    n = ref.n;
    for(int i = 0; i < n; i ++){
        for (int j = 0; j < n; j++)
          matrix[i][j] = ref.matrix[i][j];
    }

}

Matrix& Matrix::operator=(const Matrix& ref)
{
    this->n = ref.n;
    // construct by n size
    for(int i = 0; i < n; i ++){
        for (int j = 0; j < n; j++)
          matrix[i][j] = ref.matrix[i][j];
    }
    return *this;
}

long long& Matrix::operator()(const int& row, const int& column) const
{
    return this->matrix[row][column];
}

void Matrix::toIdentity()
{
    for(int i = 0; i < n; i ++)
        matrix[i][i] = 1;
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
    Matrix ans(n);
    ans.toZero();
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){

            for(int q = 0; q < n; q++)
                ans.matrix[i][j] += (this->matrix[i][q]* rhs.matrix[q][j]) % mod;

        }
    }
    return ans;
}

Matrix Matrix::power(int k) const
{
    Matrix ans(n);
    ans.toZero();
    ans.toIdentity();
    //cout << "identity\n";
    //cout<<ans;

    Matrix ret(n);
    ret = *this;
    //cout << "ret\n";
    //cout << ret;
    
    while(k > 0){
        if(k % 2 == 1)  ans = ans * ret;
        ret = ret * ret;
        k /= 2;
    }
    return ans;
    
}

Matrix constructMatrix(int n)
{   
    // construct ret Matrix
    Matrix ans(n);

    return ans;
}