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
} Node ;

Node *buildBST(int n,int *preOrder)
{
    /*if(n == 0)
        return NULL;*/

    Node *new = malloc(sizeof(Node));
    new->key = preOrder[0];
    new->ltree = new->rtree = NULL;

    if(n == 2){
        Node *last = malloc(sizeof(Node));
        last->key = preOrder[1];
        last->ltree = last->rtree = NULL;
        if(preOrder[1] > new->key)
            new->rtree = last;
        else new->ltree = last;
        return new;
    }

    int *new_array = malloc(sizeof(int)*n);
    int *new_array2 = malloc(sizeof(int)*n);
    int i;
    int j = 0;
    int k = 0;
    int mark = 0;
    for(i = 1; i < n; i ++){
        if(preOrder[i] > new->key || mark == 1){
            mark = 1;
            new_array2[k++] = preOrder[i];
        }
        else if(mark == 0)
            new_array[j++] = preOrder[i];
    }
    
    //left child
    if(j > 1)
        new->ltree = buildBST(j,new_array);
    else if(j == 1){
        Node *last = malloc(sizeof(Node));
        last->key = new_array[0];
        last->ltree = last->rtree = NULL;
        new->ltree = last;
    }
    else if(j == 0)
        new->ltree = NULL;

    //right child
    if(k > 1)
        new->rtree = buildBST(k,new_array2);
    else if(k == 1){
        Node *last = malloc(sizeof(Node));
        last->key = new_array2[0];
        last->ltree = last->rtree = NULL;
        new->rtree = last;
    }
    else if(k == 0)
        new->rtree = NULL;

    free(new_array);
    free(new_array2);
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

