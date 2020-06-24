#include <stdio.h>
#include <stdlib.h>
//#include "function.h"
// 10968 - Prefix to infix
// add paranthesis to every right tree

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;
void printInfix(Node *root);

void printInfix(Node *root)
{
    if(root != NULL){
        printInfix(root->left);
        printf("%c",root->data);
        if(root->right != NULL){
            if( root->right->data == '&' || root->right->data == '|'){
                printf("(");
                printInfix(root->right);
                printf(")");
            }
            else printInfix(root->right);
        }
    }
    else return;
}

void constructTree(Node** head)
{
    char c;

    if((*head) == NULL)
    {
        (*head) = (Node *)malloc(sizeof(Node));
		c = getchar();

		(*head)->data = c;

        (*head)->left = (*head)->right = NULL;

        if(((*head)->data=='&' || (*head)->data=='|')){
            constructTree( &(*head)->left);
            constructTree( &(*head)->right);
        }
        else return;
    }
}

void freeTree(Node *root)
{
    if (root!=NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void)
{
    int n;
    scanf("%d", &n);// the number of test cases

    while(n>0)
    {
        getchar();
        Node *root=NULL;
        constructTree(&root);// construct syntax tree
        printInfix(root);// you have to implement this function
        printf("\n");
        freeTree(root);
        --n;
    }

    return 0;
}
