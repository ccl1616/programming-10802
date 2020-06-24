#include <stdio.h>
// josephus recursion

int Josephus(int n)
{
    if (n==1) return 1;
    else if (n%2 == 0)
        return 2*Josephus(n/2)-1;
    else 
        return 2*Josephus(n/2)+1;
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d\n",Josephus(n));
    return 0;
}