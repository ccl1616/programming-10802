#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdlib>
#include <math.h>

#include "function.h"
using namespace std;
// #define WIDTH 8
// #define N 150

int biglen(int* bigInt)
{
    int i;

    for(i = 0; i <= 149; i ++){
        if(bigInt[i] == 0 && i == 0)
            return 0;
        else if(bigInt[i] == 0)
            return i;
    }
    return i;
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
    
    int j = 0;
    int count = 0;
    for(int i = len; i >= 0; i --){
        if(count == 8){
            count = 0;
            j++;
        }
        bigInt[j] += (num[i]-'0') * pow(10,count);
        count ++;
    }
    
}

BigInt::BigInt(const BigInt& num)
    :sign(num.sign)
{
    for(int i = 0; i < N; i ++){
        bigInt[i] = num.bigInt[i];
    }
}

BigInt& BigInt::operator = (const BigInt& right)
{
    sign = right.sign;
    for(int i = 0; i < N; i ++)
        bigInt[i] = right.bigInt[i];
    return *this;
}

bool BigInt::operator < (BigInt right)
{
    if(sign != right.sign)
        return sign;

    int leftlen = biglen(bigInt);
    int rightlen = biglen(right.bigInt);
    if(leftlen != rightlen)
        return (leftlen < rightlen) ^ sign;
    for(int i = leftlen-1; i >= 0; i --){
        if(bigInt[i] != right.bigInt[i])
            return (bigInt[i] < right.bigInt[i])^sign;
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

    for(int i = leftlen-1; i >= 0; i --){
        if(bigInt[i] != right.bigInt[i])
            return false;
    }
    return true;
}

bool BigInt::operator >= (BigInt cmp)
{
    if(this->bigInt < cmp.bigInt)
        return false;
    return true;
}

bool BigInt::operator <= (BigInt cmp)
{
    if(this->bigInt > cmp.bigInt)
        return false;
    return true;
}

BigInt BigInt::operator + (BigInt cmp)
{
    BigInt ans;
    int carry = 0;
    int llen = biglen(bigInt);
    int rlen = biglen(cmp.bigInt);
    int maxlen = max(llen,rlen);
    int temp,i;

    for(i = 0; i < maxlen; i ++){
        temp = bigInt[i] + cmp.bigInt[i] + carry;
        carry = temp / BASE;
        ans.bigInt[i] = temp % BASE;
    }
    ans.bigInt[i] = carry;
    
    return ans;
}

BigInt BigInt::operator - (BigInt cmp)
{
    // cout << "sign: " << sign << endl;
    BigInt ans;
    if(this->sign != cmp.sign){
        // 數值為兩者相加
        ans = *this + cmp;
        ans.sign = this->sign; //不知道為啥這行如果擺在196前面就會錯:(
        //cout << "ans sign after:" << ans.sign << endl; 
    }

    else{

        int llen = biglen(this->bigInt);
        int rlen = biglen(cmp.bigInt);
        int borrow = 0;
        int temp;
        for(int i = 0; i < max(llen,rlen); i ++){
            if( *this >= cmp ^ ans.sign )
                temp = bigInt[i] - cmp.bigInt[i] - borrow;
            else temp = cmp.bigInt[i] - bigInt[i] - borrow;

            if(temp < 0){
                borrow = 1;
                temp += BASE;
            }
            else{
                borrow = 0;
            }
            ans.bigInt[i] = temp;
        }
        ans.sign = *this < cmp;
    }

    return ans;
}

istream& operator >> (istream &input, BigInt &num)
{
    char str[2000]; 
    input >> str;

    if(str[0] == '-'){
        num.sign = 1;
        strcpy(str,&str[1]);
    }
    int len = strlen(str)-1;
    
    int j = 0;
    int count = 0;
    for(int i = len; i >= 0; i --){
        if(count == 8){
            count = 0;
            j ++;
        }
        num.bigInt[j] += (str[i]-'0') * pow(10,count);
        count ++;
    }
    return input;
}

ostream& operator << (ostream &output, BigInt &num)
{
    
    int blen = biglen(num.bigInt);
    if(blen == 0)
        cout << "0";
    else {
        if(num.sign == 1)
        cout << '-';

        int j = 0;
        
        cout << num.bigInt[blen-1];
        for(int i = blen-2; i >= 0; i--)
            cout << setw(8) << setfill('0') << num.bigInt[i];
    }
    
    return output;
}

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n)
{
    //cout << "defaulf:" << endl;
    //cout << inosuke << "/" << tanjiro << "/" << zenitsu << endl;
    // if same : ino > tan > zen
    /*
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
    */
    /*
    // t z i
    // 2-1
    zenitsu = zenitsu - tanjiro;
    // 3-1
    inosuke = inosuke - tanjiro;
    */
    for (int i = 0; i < n; i++) {
		BigInt mission;
		cin >> mission;
		if (inosuke >= tanjiro && inosuke >= zenitsu)
			inosuke = inosuke - mission;
		else if (tanjiro >= inosuke && tanjiro >= zenitsu)
			tanjiro = tanjiro - mission;
		else if (zenitsu >= inosuke && zenitsu >= tanjiro)
			zenitsu = zenitsu - mission;
	}
    /*
    char num[2000];
    while(n--) {
        cin >> num;
        BigInt mission(num);
        if(n == 2)
            zenitsu = zenitsu - mission;
        else if(n == 1)
            inosuke = inosuke - mission;
        else {
            int i = zenitsu >= inosuke;
            cout << i << endl;
            i = zenitsu <= inosuke;
            cout << i << endl;
            i = zenitsu == inosuke;
            cout << i << endl;
        }
    }
    */
}