#include <iostream>
#include <stdlib.h>
#include "function.h"
using namespace std;

// constructor
Polynomial::Polynomial(){}

Polynomial::Polynomial(const int gp, const int cof[51]){
    for(int i=gp; i>=0; i--)
        this->coefficients[i] = cof[i];
    this->greatestPower = gp;
}

Polynomial Polynomial::add(Polynomial b) const{
    Polynomial ans = *this;
    int asize = ans.greatestPower;
    int bsize = b.greatestPower;
    ans.greatestPower = asize > bsize ?asize :bsize;
    for(int i = bsize; i >= 0; i --)
        ans.coefficients[i] += b.coefficients[i];
    return ans;
}

Polynomial Polynomial::subtract(const Polynomial b) const{
    Polynomial ans = *this;
    int asize = ans.greatestPower;
    int bsize = b.greatestPower;
    ans.greatestPower = asize > bsize ?asize :bsize;
    for(int i = bsize; i >= 0; i --)
        ans.coefficients[i] += (-1) * b.coefficients[i];
    return ans;
}

Polynomial Polynomial::multiplication(const Polynomial b) const{
    Polynomial ans = Polynomial();
    Polynomial a = *this;
    int asize = a.greatestPower;
    int bsize = b.greatestPower;
    ans.greatestPower = asize + bsize;
    for(int i = 0; i <= ans.greatestPower; i ++)
        ans.coefficients[i] = 0;
    for(int i = 0; i <= asize; i ++){
        for(int j = 0; j <= bsize; j ++){
            ans.coefficients[i+j] += a.coefficients[i]*b.coefficients[j];
        }
    }
    return ans;
}

void Polynomial::output() const{
    int i = this->greatestPower;
    for(; i > 0; i --)
        cout << this->coefficients[i] << " ";
    cout << this->coefficients[0];
}