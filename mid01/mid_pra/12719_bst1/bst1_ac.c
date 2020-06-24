#include <stdio.h>
#include <stdlib.h>
//#include "function.h"
// 12719 - Binary search trees I: construction and traversal 
#define MAX_N 1000006
typedef struct Node
{
    int key;
    struct Node *ltree;
    struct Node *rtree;
    //struct Node *parent;
} Node ;
int pos = 0;
int max = 2147482647;
int min = -1;

Node *buildBST(int n,int *preOrder)
{
    //static int pos = 0,max = 2147482647,min = -1;
    
    if (preOrder[pos] == -1||preOrder[pos] < min || preOrder[pos] > max)
        return NULL;
    Node *new = malloc(sizeof(Node));
	int id = preOrder[pos];
    new->key = id;
    preOrder[pos++] = -1;

    if(pos == n){
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