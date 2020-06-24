#include <stdio.h>
#include <stdlib.h>
//#include "function.h"
// 12719 - Binary search trees I: construction and traversal 
#define MAX_N 1000006
int pos = 0;
int max = MAX_N;
int min = -1;
typedef struct Node
{
    int key;
    struct Node *ltree;
    struct Node *rtree;
} Node ;

Node *buildBST(int n,int *preOrder)
{
    Node *new = malloc(sizeof(Node));
    new->key = preOrder[pos++];
    new->ltree = new->rtree = NULL;
    if(pos != n){
        if(new->key > min && new->key < max){
            max = new->key;
            new->ltree = buildBST(n,preOrder);
            new->rtree = buildBST(n,preOrder);
        }
        else if(new->key > max){
            new->ltree = NULL;
            return NULL;
        }
    }

    return new;
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
        printInOrder(root);
        printf("\n");
        printPostOrder(root);
        printf("\n");
        freeTree(root);
    }
}

