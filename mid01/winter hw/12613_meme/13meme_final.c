#include <stdio.h>
#include <math.h>
// 12613 - Yet Another Meme Problem
// solve by math
// couc(a,b) = a*10^|b| + b
// a*b +a +b = a*10^|b| + b
// a*(b+1) = a*10^|b|
// b+1 = 10^|b|
// b = 10^n -1
// num == 9,99,999..... <= b

int main()
{
    long long int t,a,b;
    scanf("%lld",&t);
    while(t--){
        int ans = 0;
        scanf("%lld %lld",&a,&b);
        int num = 0;
        while(num <= b){
            ans ++;
            num = num*10 + 9;
        }
        printf("%lld\n",a*(ans-1));
        // ans-1 cause 0<=b had counted once
        // the number of 'a' * (all possible bs) = ans
    }
    return 0;
}