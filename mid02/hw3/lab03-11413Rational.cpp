#include <iostream>
//#include "function.h" // include definition of class Rational
using namespace std;
class Rational
{
    public:
        Rational( int = 0, int = 1 ); // default constructor
        Rational addition( const Rational & ) const; // function addition
        Rational multiplication( const Rational & ) const; // function multi.
        void printRational () const; // print rational format

    private:
        int numerator; // integer numerator
        int denominator; // integer denominator
        void reduce();
}; // end class Rational

int gcd(int a, int b);

Rational::Rational( int a, int b )
{
    numerator = a;
    denominator = b;
}

Rational Rational::addition( const Rational & b)const
{
    Rational ans;
    ans.numerator = this->numerator * b.denominator + b.numerator * this->denominator;
    ans.denominator = this->denominator * b.denominator;
    int saver = gcd (ans.numerator, ans.denominator);
    ans.numerator /= saver;
    ans.denominator /= saver;

    if(ans.denominator < 0){
        ans.denominator *= -1;
        ans.numerator *= -1;
    }
    return ans;
}

Rational Rational::multiplication( const Rational & b )const
{
    Rational ans;
    ans.numerator = this->numerator * b.numerator;
    ans.denominator = this->denominator * b.denominator;
    int saver = gcd (ans.numerator, ans.denominator);
    ans.numerator /= saver;
    ans.denominator /= saver;

    if(ans.denominator < 0){
        ans.denominator *= -1;
        ans.numerator *= -1;
    }
    return ans;
}

void Rational::printRational()const
{
    cout << numerator << "/" << denominator << endl;
}


int main()
{
    char s1;
    int s2, s3, s4, s5;

    Rational x;
    while(cin >>s1>>s2>>s3>>s4>>s5)
    {
        if(cin.eof())
        {
            break;
        }
        Rational c(s2, s3), d(s4, s5);
        if(s1 == '+')
        {
            x = c.addition( d ); // adds object c and d; sets the value to x
            x.printRational(); // prints rational object x
        }
        else if(s1 == '*')
        {
            x = c.multiplication( d ); // multiplies object c and d
            x.printRational(); // prints rational object x
        }
    }
}

int gcd(int a, int b){
    return (b == 0) ? a : gcd(b, a % b);
}