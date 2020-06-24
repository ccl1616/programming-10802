#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 12183 - Fairy Testing
// http://codepad.org/ynaLv5bv過不了ㄉ
// http://codepad.org/cEIgQ75C 

#define maxsize 100003
char str[900005]; //!
char tokenset[maxsize];
int pos;
int n,m;

typedef struct node{
    int value; // This is the value of the subtree, not the ID number
    int name; //the id of varaible
    struct node *left,*right;
    struct node *parent; //pointing to the parent node
}Node;

Node *variable[maxsize]; // This array stores the pointers pointing to the tree nodes. For example, variable[0] points to the node with ID number 0.

int getNum()
{
    int temp = 0;
    temp = str[pos++]-'0';
    while(str[pos] != ']'){
        temp = temp*10;
        temp += str[pos++]-'0';
    }
    pos++;
    return temp;
}

Node* constructTree(Node* head)
{
    char c;
    /* // 不可以放這個！
    if(nodenum > m)
        return NULL;*/
    
    int temp;
    Node *new;
    new = (Node *)malloc(sizeof(Node));
    new->value = 0;
    new->parent = head;
    new->left = new->right = NULL;

    c = str[pos++];
    if(c == '[' ){
        temp = getNum();
        new->name = temp;
        variable[temp] = new;
        return new;
    }
    else {
        if(c == '&')
            new->name = -1;
        else new->name = -2;
        new->left = constructTree(new);
        new->left->parent = new;
        new->right = constructTree(new);
        new->right->parent = new;
    }
    return new;
}

void freeTree(Node* root)
{
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void changeParents(Node* parent)
{
    Node *p,*ln,*rn; //leftnode, rightnode

    // root case
    if(parent == NULL)
        return;
        
    // not the root case
    p = parent;
    // & case
    if(p->name == -1){
        ln = p->left;
        rn = p->right;
        if(p->value != (ln->value && rn->value) ){
            p->value = !p->value;
            changeParents(p->parent);
        } 
        return;
    }
    // | case
    else if(p->name == -2){
        ln = p->left;
        rn = p->right;
        if(p->value != (ln->value || rn->value) ){
            p->value = !p->value;
            changeParents(p->parent);
        } 
        return;
    }
    // variable case
    else{
        p->value = !p->value;
        changeParents(p->parent);
    }
    return;
}

int main()
{
    int t,flipid;
    scanf("%d",&t);
    while(t--){
        memset(str, 0, sizeof(str)); //!!
        memset(variable,0,sizeof(variable));
        scanf("%d %d",&n,&m);
        scanf("%s",str);
        pos = 0;
        Node *root = constructTree(root);
        Node *flipnode;
        root->parent = NULL;

        while(m --){
            scanf("%d",&flipid);
            flipnode = variable[flipid];
            changeParents(flipnode);
            printf("%d\n",root->value);
        }
        freeTree(root);
    }
    return 0;
}