/* This program construct a syntax tree from an infix Boolean expression.
   The expression has no parenthesis, and no error checking.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 10966 - Infix to syntax tree 

#define MAXEXPR 256
#define NUMSYM 6
char expr[MAXEXPR];
int pos;

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM]="ABCD&|";

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);

/* create a node without any child.*/
BTNode* makeNode(char c){
    int i;
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    for (i = 0; i < NUMSYM; i++)
        if (c == sym[i])
        {
            node->data = i;
            break;
        }
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTNode* FACTOR(){
    char c;
    BTNode *node = NULL;

    if (pos >= 0) {
        c = expr[pos--];
        if (c>= 'A' && c<='D'){// factor = ID
            node = makeNode(c);
        } 
        else if (c== ')') {   // factor = (EXPR)
            node = EXPR();
            if(expr[pos--]!= '(') {
                printf("Error!\n");
                freeTree(node);
            }
        }
    }
    return node;
}


/* parse an infix expression and generate a syntax tree. */
BTNode* EXPR(){
    char c;
    BTNode *node = NULL, *right=NULL;

    if (pos >= 0) {   // if the expression has length >= 1.
        right = FACTOR(); 

        if (pos > 0) {// 1. the EXPR OP ID case
            c = expr[pos]; // |
            if (c=='&' || c=='|'){
                node = makeNode(c); 
                node->right = right; 
                pos--; 
                node->left = EXPR(); 
            }
            else node = right; // 2. EXPR = ID
        }
        else
            node = right; // 2. EXPR = ID
    }
    return node;
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

int main(){
    
    while( scanf("%s",expr)!= EOF){
        pos = strlen(expr)-1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        freeTree(root);
    }
    return 0;
}
