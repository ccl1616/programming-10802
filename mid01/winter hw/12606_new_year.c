#include <stdio.h>
// 12606 - Happy New Year 
int main()
{
    int max = 0;
    int min = __INT32_MAX__;
    int temp;
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n+1; i ++){
        scanf("%d",&temp);
        min = temp < min ?temp:min;
        max = temp > max ?temp:max;
    }
    printf("%d\n",2 * (max-min) );
    return 0;
}