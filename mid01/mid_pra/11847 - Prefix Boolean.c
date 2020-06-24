#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//11847 - Prefix Boolean expression
int a[5];
char str[50];
int pos;

typedef struct _node{
    char data;
    struct _node *left,*right;
}Node;

void constructTree(Node** head)
{
    char c;

    if((*head)==NULL)
    {
        (*head) = (Node *)malloc(sizeof(Node));
        //c = getchar();
        c = str[pos++];

        (*head)->data = c;

        (*head)->left = (*head)->right = NULL;

        if((*head)->left == NULL && ((*head)->data=='&' || (*head)->data=='|'))
            constructTree( &(*head)->left);
        if((*head)->right == NULL && ((*head)->data=='&' || (*head)->data=='|'))
            constructTree( &(*head)->right);
    }
}

int printInfix(Node *root)
{
    char c;
    int op1,op2;
    c = root->data;
    //printf("char:%c\n",c);
    if(c == '&' || c == '|'){
        op1 = printInfix(root->left);
        op2 = printInfix(root->right);
        if(c == '&')
            return op1&op2;
        else return op1|op2;
    }
    else return a[c-65];
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

void make_binary(int size)
{
    Node *tree = NULL;
    constructTree(&tree);
    for(int i = 0; i < pow(2,size); i ++){
        memset(a,0,sizeof(a));
        int n = i;
        int pos = size-1;
        while(n != 0){
            a[pos--] = n % 2;
            n = n/2;
        }
        //pos--;
        
        for(int i = 0; i < size; i ++)
            printf("%d ",a[i]);
        printf("%d\n",printInfix(tree));
    }
    free(tree);
}

int main()
{
    int size = 4;
    scanf("%s",str);
    make_binary(size);
    return 0;
}
