#include <iostream>
#include <string.h>
#include <iomanip>
#include <cmath>

using namespace std;
class BigInt
{
private:
    const static int N = 1100;
    const static int WIDTH = 8, BASE = 100000000;
    int bigInt[N];
public:
    // constructor
    BigInt();
    BigInt(char*);
    BigInt(const BigInt&); 
    // copy assignment operator
    BigInt& operator = (const BigInt&);
    
    // arithmetic operator
    BigInt operator + (BigInt);
    BigInt operator - (int);
    
    // insertion & extraction operator
    friend istream& operator >> (istream&, BigInt&);
    friend ostream& operator << (ostream&, BigInt&);
    ~BigInt();
};

void solution(BigInt &s);


int biglen(int* array)
{
    int i = 0;
    for(i = 0; i < 30100; i ++){
        if(array[i] == 0 && i == 0)
            return 0;
        else if(array[i] == 0)
            return i;
    }
    return i;
}

BigInt::BigInt()
{
    bigInt[0] = 1;
    for(int i = 1; i < N; i ++)
        bigInt[i] = 0;
}

BigInt::BigInt(char* in)
{
    int j = 0;
    int count = 0;
    int len = strlen(in)-1;
    for(int i = len; i >= 0; i--){
        if(count == 8){
            count = 0;
            j++;
        }
        else count++;
        bigInt[j] = (in[i]-'0') * pow(10,count);
    }
}

BigInt::BigInt(const BigInt& in)
{
    for(int i = 0; i < N; i ++){
        bigInt[i] = in.bigInt[i];
    }
} 

BigInt::~BigInt()
{}

BigInt& BigInt::operator = (const BigInt& in)
{
    for(int i = 0; i < N; i ++)
        bigInt[i] = in.bigInt[i];
    return *this;
}

BigInt BigInt::operator + (BigInt cmp)
{
    BigInt ans;
    int carry = 0;
    int llen = biglen(bigInt);
    
    int temp,i;

    for(i = 0; i < llen; i ++){
        temp = bigInt[i]*2 + carry;
        carry = temp / BASE;
        ans.bigInt[i] = temp % BASE;
    }
    ans.bigInt[i] = carry;
    
    return ans;
}

BigInt BigInt::operator - (int one)
{
    BigInt ans;
    ans = *this;
    ans.bigInt[0]--;
    return ans;
}


istream& operator >> (istream& in, BigInt& s)
{
    char str[30100];
    in >> str;
    s = BigInt(str);
    return in;
}

ostream& operator << (ostream& out, BigInt& s)
{
    int len = biglen(s.bigInt);
    if(len == 0)
        cout << '0';
    else{
        cout << s.bigInt[len-1];
        for(int i = len-2; i >= 0; i --){
            cout << setw(8) << setfill('0') << s.bigInt[i];
        }
    }
    return out;
}

void solution(BigInt &s)
{
    int temp;
    cin >> temp;
    while(temp--){
        s = s+s;
    }
    s = s-1;
}

int main()
{
    int n; 
    cin >> n;
    
    while(n--){
        BigInt hi;
        solution(hi);
        cout << hi << endl;
    }
}
