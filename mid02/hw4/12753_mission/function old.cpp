#include <iostream>
#include <iomanip>
#include<string.h>
#include<cstdlib>
#include<math.h>

#include "function.h"
using namespace std;
// #define WIDTH 8
// #define N 150

int biglen(int* bigInt)
{
    int i;

    for(i = 149; i >= 0; i --){
        if(bigInt[i] == 0 && i == 149)
            return 0;
        else if(bigInt[i] == 0)
            return 149-i;
    }
    return 150;
}

BigInt::BigInt()
    :sign(0)
{
    //sign = 0;
    for(int i = 0; i < N; i ++)
        bigInt[i] = 0;
}

BigInt::BigInt(char* num)
    :sign(0)
{
    for(int i = 0; i < N; i ++)
        bigInt[i] = 0;

    if(num[0] == '-'){
        sign = 1;
        num = &num[1];
    }
    int len = strlen(num)-1;
    
    int j = N-1;
    int count = 0;
    for(int i = len; i >= 0; i --){
        if(count == 8){
            count = 0;
            j--;
        }
        bigInt[j] += (num[i]-'0') * pow(10,count);
        count ++;
    }
    
}

BigInt::BigInt(const BigInt& num)
    :sign(num.sign)
{

    for(int i = 0; i < N; i ++){
        bigInt[i] = 0;
        bigInt[i] = num.bigInt[i];
    }
}

BigInt& BigInt::operator = (const BigInt& right)
{
    sign = right.sign;
    for(int i = 0; i < N; i ++)
        this->bigInt[i] = right.bigInt[i];
    return *this;
}

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n)
{
    int i = tanjiro<zenitsu;
    cout << "smaller: " << i << endl;
}

bool BigInt::operator < (BigInt right)
{
    if(sign != right.sign)
        return sign;

    int leftlen = biglen(bigInt);
    int rightlen = biglen(right.bigInt);
    if(leftlen != rightlen)
        return (leftlen < rightlen) ^ sign;
    for(int i = leftlen; i >= 1; i --){
        if(bigInt[N-i] != right.bigInt[N-i])
            return (bigInt[N-i] < right.bigInt[N-i])^sign;
    }
    return false;
}

bool BigInt::operator > (BigInt right)
{
    if(*this < right || *this == right)
        return false;
    return true;
}

bool BigInt::operator == (BigInt right)
{
    if(this->sign != right.sign)
        return false;

    int leftlen = biglen(bigInt);
    int rightlen = biglen(right.bigInt);
    if(leftlen != rightlen)
        return false;

    for(int i = leftlen; i >= 1; i --){
        if(bigInt[N-i] != right.bigInt[N-i])
            return false;
    }
    return true;
}
/*
bool BigInt::operator <= (BigInt cmp)
{
    
}

bool BigInt::operator >= (BigInt cmp)
{

}

BigInt BigInt::operator + (BigInt cmp)
{

}
BigInt BigInt::operator - (BigInt cmp)
{

}*/

istream& operator >> (istream &input, BigInt &num)
{
    char str[2000]; 
    input >> str;

    if(str[0] == '-'){
        num.sign = 1;
        strcpy(str,&str[1]);
    }
    int len = strlen(str)-1;
    
    int j = 149;
    int count = 0;
    for(int i = len; i >= 0; i --){
        if(count == 8){
            count = 0;
            j--;
        }
        num.bigInt[j] += (str[i]-'0') * pow(10,count);
        count ++;
    }
    

    return input;
}

ostream& operator << (ostream &output, BigInt &num)
{
    
    if(num.sign == 1)
        cout << '-';
    if(num.bigInt[149] == 0)
        cout << "0";
    else{
        int blen = biglen(num.bigInt);
        while(blen--){
            cout << num.bigInt[149-blen];
        }
    }
    cout << endl;

    return output;
}