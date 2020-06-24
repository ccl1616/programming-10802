#include <stdio.h>
#include <stdlib.h>
//#include "function.h"
#define MAX_N 100005

typedef struct _Node{
    int key;
    struct _Node *ltree;
    struct _Node *rtree;
}Node ;

void printArray(int *a,int n)
{
    for(int i = 0; i < n; i ++)
        printf("%d ",a[i]);
    printf("\n");
    return;
}
Node *build(int *array,int n)
{
    if(n == 0)
        return NULL;
    Node *new = malloc(sizeof(Node));
    new->key = array[0];
    new->ltree = new->rtree = NULL;

    if(n == 2){
        Node *last = malloc(sizeof(Node));
        last->key = array[1];
        last->ltree = last->rtree = NULL;
        if(array[1] > new->key)
            new->rtree = last;
        else new->ltree = last;
        return new;
    }
    
    int i;
    for(i = 1; i < n; i ++){
        if(array[i] > new->key)
            break;
    }
    
    int *new_array = malloc(sizeof(int)*i);
    int j;
    if(i != 1){
        j = 0;
        for(int start = 1; start <= i-1; start ++){
            new_array[j++] = array[start];
        }
        //printArray(new_array,j);
        new->ltree = build(new_array,i-1);
    }
    else new->ltree = NULL;

    j = 0;
    for(int start = i; start <= n; start ++){
        new_array[j++] = array[start];
    }
    //printf("%d %d\n",i,j);
    //printArray(new_array,j);
    new->rtree = build(new_array,n-i);

    return new;
}

void printIn(Node *root)
{
    if(root != NULL){
        printIn(root->ltree);
        printf("%d ",root->key);
        printIn(root->rtree);
    }
    return;
}
void printPost(Node *root)
{
    if(root != NULL){
        printPost(root->ltree);
        printPost(root->rtree);
        printf("%d ",root->key);
    }
    return;
}
void freeT(Node *root)
{
    if(root != NULL){
        freeT(root->ltree);
        free(root->rtree);
        free(root);
    }
    return;
}
int input[MAX_N];

int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i = 0; i < n; i ++)
            scanf("%d",&input[i]);
        
        
        Node *root = build(input,n);
        
        printIn(root);
        printf("\n");
        printPost(root);
        printf("\n");
        freeT(root);
    }
    return 0;
}
