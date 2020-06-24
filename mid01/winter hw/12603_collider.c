#include <stdio.h>
#include <string.h>
// 12603 - Launch of Collider 
#define max 200005
int n;
int ans = __INT32_MAX__;
char str[max];
int a[max];

int main()
{
    scanf("%d",&n);
    scanf(" %s",str);

    scanf("%d",&a[0]);
    for(int i = 1; i < n; i ++){
        scanf("%d",&a[i]);
        
        if(str[i] == 'L' && str[i-1] == 'R'){
            if((a[i]-a[i-1]) < ans)
                ans = (a[i]-a[i-1]);
        }
        /*
        if(str[i] == 'R' && str[i+1] =='L'){
            if(a[i+1]-a[i] < ans)
                ans = a[i+1]-a[i];
        }*/
    }
    if(ans == __INT32_MAX__) printf("-1\n");
    else printf("%d\n",ans/2);
    return 0;
}