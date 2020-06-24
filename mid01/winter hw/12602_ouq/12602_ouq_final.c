#include <stdio.h>
// 12602 - OuQ String
int k,l,r;
char str[4] = "OuQ";
long long size[52];

char func(int k, long long pos)
{
    if(k == 1)
        return str[pos];
    else if(pos == 0 ) //sk 的第一個字 必為O
        return 'O';
    else if(pos == 1+size[k-1]) //sk的中間字 必為u
        return 'u';
    else if(pos == size[k]-1 ) //sk的最後一個字 Q
        return 'Q';
        
    else{
        if(pos < 1+size[k-1]) 
            return func(k-1,pos-1);
        else return func(k-1,pos-2-size[k-1]);
    }
    return 0 ;
}

int main()
{
    size[1] = 3;
    for(int i = 2; i <= 50; i ++)
        size[i] = 3+ 2*size[i-1];

    while(scanf("%d %d %d",&k,&l,&r)!= EOF ){
        // k is level
        while(l <= r){
            printf("%c",func(k,l));
            l ++;
        }
        printf("\n");
    }
    return 0;
}