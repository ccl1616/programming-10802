#include "function.h"
#include<string.h>
#include <iomanip>
#include<cmath>

int length(int* bigInt) {
    int len;
    for(len = 149; len>=0 && bigInt[len]==0; len--) {}
    return len+1;
}

BigInt::BigInt()
    :sign(0)
{
    for(int i = 0; i < N; i++)
        bigInt[i] = 0;
}

BigInt::BigInt(char* num)
    :sign(0)
{
    if(num[0]=='-') {
        sign = 1;
        num = &num[1];
    }
    int len = strlen(num);
    for(int i = 0; i < N; i++)
        bigInt[i] = 0;
    for(int i = 0; i < len; i++) {
        bigInt[(len-i-1)/8] *= 10;
        bigInt[(len-i-1)/8] += num[i]-'0';
    }
}

BigInt::BigInt(const BigInt& num)
    :sign(num.sign), bigInt{0}
{
    for(int i = 0; i < N; i++)
        bigInt[i] = num.bigInt[i];
}

BigInt &BigInt::operator = (const BigInt& right) {
    sign = right.sign;
    for(int i = 0; i < N; i++)
        bigInt[i] = right.bigInt[i];
    return *this;
}

bool BigInt::operator < (BigInt right) {
    if(sign != right.sign)
        return sign;

    int leftLen = length(bigInt);
    int rightLen = length(right.bigInt);
    if(leftLen != rightLen)
        return (leftLen < rightLen) ^ sign;
    for(int i = leftLen-1; i >= 0; i--) {
        if(bigInt[i] != right.bigInt[i])
            return (bigInt[i] < right.bigInt[i]) ^ sign;
    }
    return false;
}
bool BigInt::operator > (BigInt right) {
    if(*this<right || *this==right)
        return false;
    return true;
}
bool BigInt::operator == (BigInt right) {
    if(sign != right.sign)
        return false;

    int leftLen = length(bigInt);
    int rightLen = length(right.bigInt);
    if(leftLen != rightLen)
        return false;
    for(int i = leftLen-1; i >= 0; i--) {
        if(bigInt[i] != right.bigInt[i])
            return false;
    }
    return true;
}
bool BigInt::operator >= (BigInt right) {
    if(*this < right)
        return false;
    return true;
}
bool BigInt::operator <= (BigInt right) {
    if(*this > right)
        return false;
    return true;
}

BigInt BigInt::operator + (BigInt right) {
    BigInt result;
    int leftLen = length(bigInt);
    int rightLen = length(right.bigInt);
    int carry = 0, i, ans;
    if(sign == right.sign) {
        for(i = 0; i < max(leftLen, rightLen); i++) {
            ans = bigInt[i] + right.bigInt[i] + carry;
            carry = ans/BASE;
            result.bigInt[i] = ans%BASE;
        }
        result.bigInt[i] = carry;
        result.sign = sign;
    }
    else {
        right.sign = !right.sign;
        result = *this - right;
    }
    return result;
}

BigInt BigInt::operator - (BigInt right){
    BigInt result;
    int leftLen = length(bigInt);
    int rightLen = length(right.bigInt);
    int borrow = 0, i, ans;
    if(sign == right.sign) {
        result.sign = *this < right;
        sign = 0; right.sign = 0;
        for(i = 0; i < max(leftLen, rightLen); i++) {
            if(*this >= right)
                ans = bigInt[i] - right.bigInt[i] - borrow;
            else
                ans = right.bigInt[i] - bigInt[i] - borrow;
            if(ans < 0) {
                borrow = 1;
                result.bigInt[i] = ans + BASE;
            }
            else {
                borrow = 0;
                result.bigInt[i] = ans;
            }
        }
    }
    else {
        right.sign = !right.sign;
        result = *this + right;
    }
    return result;
}

istream& operator >> (istream& input, BigInt& num) {
    char in[2000];
    input >> in;
    if(in[0]=='-') {
        num.sign = 1;
        strcpy(in, &in[1]);
    }
    int len = strlen(in);
    for(int i = 0; i < len; i++) {
        num.bigInt[(len-i-1)/8] *= 10;
        num.bigInt[(len-i-1)/8] += in[i]-'0';
    }

    return input;
}
ostream& operator << (ostream& output, BigInt& num) {
    if(num.sign)
        output << '-';
    int len;
    len = length(num.bigInt);
    if(len==0)
        output << "0";
    else {
        output << num.bigInt[len-1];
        for(int i = len-2; i >= 0; i--)
            output << setw(8)<< setfill('0') << num.bigInt[i];
    }

    return output;
}

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n) {
    char num[2000];
    while(n--) {
        cin >> num;
        BigInt mission(num);
        if(inosuke >= tanjiro) {
            if(inosuke >= zenitsu)
                inosuke = inosuke - mission;
            else
                zenitsu = zenitsu - mission;
        }
        else {
            if(tanjiro >= zenitsu)
                tanjiro = tanjiro - mission;
            else
                zenitsu = zenitsu - mission;
        }
    }

}