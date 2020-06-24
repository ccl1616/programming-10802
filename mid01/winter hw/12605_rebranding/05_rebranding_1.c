#include <stdio.h>
#include <string.h>
// 12605 - Rebranding
int n,m;
char str[200005];
char x[2];
char y[2];

int main()
{
    scanf("%d %d",&n,&m);
    scanf("%s",str);
    
    while(m--){
        scanf("%s",x);
        scanf("%s",y);

        for(int i = 0; i < n; i ++){
            if(str[i] == x[0])
                str[i] = y[0];
            else if(str[i] == y[0])
                str[i] = x[0];
        }
    }
    printf("%s\n",str);
    
    return 0;
}