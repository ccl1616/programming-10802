#include <stdio.h>
#include <math.h>
// 12613 - Yet Another Meme Problem
// TLE 0/5
#define min(a,b) a>b?b:a
#define max(a,b) a>b?a:b
long long int a,b;
long long int i, j;
long long int ans;

long long int count_digit(long long int num)
{
    long long int count = 0;
    while(num != 0){
        count ++;
        num = num/10;
    }
    return count;
}

long long int conc(long long int c,long long int d)
{
    long long int conc_ans = 0;
    
    //long long int d_digit = count_digit(d);
    
    long long int num = d;
    long long int count = 0;
    while(num != 0){
        count ++;
        num = num/10;
    }
    //printf("count : %lld\n",count);
    conc_ans = c * pow(10,count) + d;
    return conc_ans;
}

int main()
{
    int testcase;
    scanf("%d",&testcase);
    while(testcase--){
        scanf("%lld %lld",&a,&b);
        ans = 0;
        //printf("couc : %lld\n",conc(a,b));
        
        for(i = 1; i <= a; i ++){
            for(j = 1; j <= b; j ++){
                if(i*j +i +j == conc(i,j) ){
                    ans ++;
                }
            }
        }    
        printf("%lld\n",ans);
    }
    return 0;
}