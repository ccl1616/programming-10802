// Author: justin0u0<dancinglinkxalgorithm@gmail.com>
#include <iostream>
#include <cstdlib>
//#include "function.h"
using namespace std;

const int mod = 1000000009;

class Matrix {
  private:
    int n;
    long long** matrix;
    
  public:
    Matrix() {
      n = 0;
      matrix = nullptr;
    }
    ~Matrix();

    Matrix(int n);
    Matrix(const Matrix& ref);

    Matrix& operator=(const Matrix& ref);

    long long& operator()(const int& row, const int& column) const;

    void toIdentity();
    void toZero() {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
          matrix[i][j] = 0;
      }
    }
    Matrix operator*(const Matrix& rhs) const;
    Matrix power(int k) const;

    friend ostream& operator<<(ostream& os, const Matrix& matrix) {
      for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++)
          os << matrix(i, j) << ' ';
        os << endl;
      }
      return os;
    }
};

// TODO: Construct a matrix
Matrix constructMatrix(int n);

// -----------------------function.cpp------------------------------------
Matrix::~Matrix()
{
    for(int i = n-1; i > 0; i --)
        delete[] matrix[i];
    delete[] matrix;
}

Matrix::Matrix(int n)
{
    this->n = n;
    // construct by n*n size
    matrix = new long long*[n];
    for(int i = 0; i < n; i ++){
        matrix[i] = new long long[n];
    }
    toZero();
}

Matrix::Matrix(const Matrix& ref)
{
    n = ref.n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
          this->matrix[i][j] = ref.matrix[i][j];
    }
}

Matrix& Matrix::operator=(const Matrix& ref)
{
    this->n = ref.n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
          this->matrix[i][j] = ref.matrix[i][j];
    }
    return *this;
}

long long& Matrix::operator()(const int& row, const int& column) const
{
    return this->matrix[row][column];
}

void Matrix::toIdentity()
{
    int i;
    int j = 0;
    for(int i = 0; i < n; i ++){
        matrix[i][j++] = 1;
    }
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
    Matrix ans(n);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){

            for(int q = 0; q < n; q++)
                ans.matrix[i][j] += this->matrix[i][q]* rhs.matrix[q][j];

        }
    }
    return ans;
}

Matrix Matrix::power(int k) const
{
    Matrix ans(n);
    ans.toIdentity();

    // make a multiplier by its size
    Matrix multiplier(n);
    int j = 1;
    for(int i = 0; i < n; i ++ )
        multiplier.matrix[i][j++] = 1;
    for(int i = 0; i < n; i ++)
        multiplier.matrix[n-1][i] = 1;
    
    while(k--){
        ans = ans * multiplier;
    }
    
    return ans;
}

Matrix constructMatrix(int n)
{   
    // construct base Matrix
    Matrix ans(n);
    ans.toIdentity();
    //cout << ans;
    return ans;
}


// -----------------------main.cpp------------------------------------
int main() {
  int n, m;
  cin >> n >> m;
  if (m <= n) {
    cout << 1 << endl;
  } 
  else {
    Matrix base = constructMatrix(n);
    
    base = base.power(m - n);

    //cout << base;
    
    int ans = 0;
    for (int i = 0; i < n; i++)
      ans = (ans + base(n - 1, i)) % mod;
    cout << ans << endl;
  }
  return 0;
}
