#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 110972 - Remove unnecessary parentheses
// http://codepad.org/cQLdzDOb

#define MAXEXPR 256
#define NUMSYM 6
char expr[MAXEXPR];
int pos;

//typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM]="ABCD&|";

typedef struct _Node {
    char data;
    struct _Node *left, *right;
} BTNode;

BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);

/* create a node without any child.*/
BTNode* makeNode(char c){
    //int i;
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
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

void printInfix(BTNode *root)
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

BTNode* FACTOR(){
    char c;
    BTNode *node = NULL;

    c = expr[pos--];
    if (c>= 'A' && c<='D'){// factor = ID
        node = makeNode(c);
    } 
    else if (c== ')') {   // factor = (EXPR)
        node = EXPR();
        pos--;
    }
    
    return node;
}


/* parse an infix expression and generate a syntax tree. */
BTNode* EXPR(){
    char c;
    BTNode *node = NULL, *right=NULL;
    if (pos>=0) {   // if the expression has length >= 1.
        right = FACTOR();

        c = expr[pos];
        if (c=='&' || c=='|'){
            node = makeNode(c);
            pos--;
            node->right = right;
            node->left = EXPR();
        }
        else node = right; // 2. EXPR = ID
    }
    return node;
}

int main(){
    scanf("%s",expr);
    pos = strlen(expr)-1;
    BTNode *root = EXPR();
    printInfix(root);
    //printf("\n");
    freeTree(root);
    
    return 0;
}
