#include <stdio.h>
#include <string.h>
// 12602 - OuQ String
// 2/4 re

char s[4] = "OuQ";
char temp[100000];
char str[100000];

void makestr(int t)
{
    char temp_o[2] = "O";
    char temp_u[2] = "u";
    char temp_q[2] = "Q";
    if(t == 0)
        strcpy(str,s);
    else {
        strcpy(temp,s);
        while(t--){
            memset(str,0,sizeof(str));
            strcpy(str,temp_o);
            strcat(str,temp);
            strcat(str,temp_u);
            strcat(str,temp);
            strcat(str,temp_q);
            strcpy(temp,str);
        }
        strcpy(str,temp);
    }
}

int main()
{
    unsigned long long int t,l,r;
    while(scanf("%llu %llu %llu",&t,&l,&r) != EOF){
        memset(str,0,sizeof(str));
        memset(temp,0,sizeof(temp));

        makestr(t-1);
        for(long long int i = l; i <= r; i ++){
            printf("%c",str[i]);
        }
        putchar('\n');
    }
    return 0;
}