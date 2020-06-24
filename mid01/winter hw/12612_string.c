#include <stdio.h>
#include <string.h>
// 12612 - Queries on a String
int main()
{
    char str[1000005];
    char temp;
    int t;
    scanf("%s",str);
    scanf("%d",&t);
    while(t--){
        int l,r,k;
        scanf("%d %d %d",&l,&r,&k);
        int len = r-l+1;
        k %= len; // !!!!!!
        l -= 1;
        r -= 1;
        while(k--){
            temp = str[r];
            for(int i = r; i > l; i --)
                str[i] = str[i-1];
            str[l] = temp;
        }
    }
    printf("%s\n",str);
    return 0;
}