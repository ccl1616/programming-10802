#include <stdio.h>
// insertion sort

void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void insertion(int a[],int size)
{
    for(int i = 0; i < size; i ++){
        int temp = a[i];
        int j = i-1;

        // 重點 要怎麼在已經檢查過得堆中再次一個一個比較
        while(j >= 0 && temp < a[j]){
            a[j+1] = a[j];
            j -= 1;
        }
        a[j+1] = temp;
    }
}

int main()
{
    //int a[1000];
    int size;
    scanf("%d",&size);

    int a[size];
    for(int i = 0; i < size; i ++)
        scanf("%d",&a[i]);
        
    insertion(a,size);
    for(int i = 0; i < size; i ++)
        printf("%d ",a[i]);
    printf("\n");

    return 0;
}