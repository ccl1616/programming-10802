#include <stdio.h>
#include <stdlib.h>
//#include "function.h"
// 12719 - Binary search trees I: construction and traversal 
#define MAX_N 1000006
int pos = 0;
int max = TMP_MAX;
int max_prev;
int min = -1;
typedef struct Node
{
    int key;
    struct Node *ltree;
    struct Node *rtree;
    //struct Node *parent;
} Node ;

Node *buildBST(int n,int *preOrder)
{
    static int pos = 0,max = 2147482647,min = -1;
    int id = preOrder[pos];
    if(id == -1 ||id > max || id < min)
        return NULL;
    Node *new = malloc(sizeof(Node));
    new->key = id;
    preOrder[pos++] = -1;

    if(pos >= n){
        min = -1;
        max = 2147482647;
        pos = 0;
        new->ltree = new->rtree = NULL;
        return new;
    }
    int temp = max;
    max = new->key;
    new->ltree = buildBST(n,preOrder);
    max = temp;

    temp = min;
    min = new->key;
    new->rtree = buildBST(n,preOrder);
    min = temp;
    
    return new;
}

void printPreOrder(Node *ptr)
{
    if(ptr != NULL){
        printf("%d ",ptr->key);
        printPreOrder(ptr->ltree);
        printPreOrder(ptr->rtree);
    }
}

void printInOrder(Node *ptr)
{
    if(ptr != NULL){
        printInOrder(ptr->ltree);
        printf("%d ",ptr->key);
        printInOrder(ptr->rtree);
    }
    return;
}
void printPostOrder(Node *ptr)
{
    if(ptr != NULL){
        printPostOrder(ptr->ltree);
        printPostOrder(ptr->rtree);
        printf("%d ",ptr->key);
    }
    return;
}
void freeTree(Node *ptr)
{
    if(ptr){
        freeTree(ptr->ltree);
        freeTree(ptr->rtree);
        free(ptr);
    }
    return;
}

int n;
int preOrder[MAX_N];

int main() 
{
    int T; scanf("%d", &T);
    for(int t = 0; t < T; t++)
    {
        printf("test %d : \n", t);
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            scanf("%d", &preOrder[i]);
        Node *root = buildBST(n, preOrder);
        /*
        printPreOrder(root);
        printf("\n");*/
        
        printInOrder(root);
        printf("\n");
        printPostOrder(root);
        printf("\n");
        freeTree(root);
    }
}

