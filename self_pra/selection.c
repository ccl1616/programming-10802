#include <stdio.h>
// selection sort
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a[10000];

    int t;
    scanf("%d",&t);

    for(int i = 0; i < t; i ++)
        scanf("%d ",&a[i]);

    for(int i = 0; i < t-1; i ++){
        // 把當前的作為最小 min是地min位為當前最小
        int min = i;
        for(int j = i+1; j < t; j ++){
            if(a[j] < a[min] )
                min = j;
        }
        // 若i==min 則不會有差別
        swap(&a[i],&a[min]); 
    }

    for(int i = 0; i < t; i ++)
        printf("%d ",a[i]);
    
    printf("\n");
    return 0;
}