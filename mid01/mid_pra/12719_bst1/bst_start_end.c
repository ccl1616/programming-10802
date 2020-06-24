#include <stdio.h>
#include <stdlib.h>
//#include "function.h"
#define MAX_N 1000006
// bst with start,end version
typedef struct _Node
{
    int key;
    struct _Node *ltree;
    struct _Node *rtree;
}Node ;


Node *build(int *array,int start,int end,int n)
{
    if(start > end)
        return NULL;
    Node *new = malloc(sizeof(Node));
    new->key = array[start];
    int i;
    for(i = start; i <= end; i ++){
        if(array[i] > new->key)
            break;
    }
    new->ltree = build(array,start+1,i-1,n);
    new->rtree = build(array,i,end,n);
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
        Node *root = build(input,0,n-1,n);
        printIn(root);
        printf("\n");
        printPost(root);
        printf("\n");
        freeT(root);
    }
    return 0;
}
