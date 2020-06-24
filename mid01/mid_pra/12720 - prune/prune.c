#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 12720 - Binary search trees II: pruning
int n;
#define max_s 100005
int in_data[max_s];
int parent[max_s];
char place[max_s];

typedef struct _node{
    //char place[max_s];
    int data;
    struct _node *left,*right,*up;
}Node;

Node *tree[max_s];

void traversal(Node *root)
{
    if(root != NULL){
        printf("%d ",root->data);
        traversal(root->left);
        traversal(root->right);
    }
    return;
}

int familyCase(Node *target)
{
    // invalid case return 1
    if(target->up == NULL)
        return 0;
    Node* parent;
    parent = target->up;
    if(parent->left == NULL || parent->right == target){
        if(target->data < parent->data)
            return 1; 
        else return 0;
    }
    else if(parent->right == NULL || parent->left == target){
        if(target->data > parent->data)
            return 1;
        else return 0;
    }
    else return 0;
}

int grandCase(Node *target,Node* grand)
{
    // invalid case return 1
    if(grand->up == NULL)
        return 0;
    Node *ggran = grand->up;
    if(ggran->left == grand){
        if(ggran->data < target->data)
            return 1;
    } 
    else if(ggran->right == grand){
        if(target->data < ggran->data)
            return 1;
    }
    if(grandCase(target,ggran))
            return 1;
    else return 0;
}


int isBadLeaf(Node* target)
{
    // if isbadleaf return 1
    if(target == NULL || target->up == NULL)
        return 0;
    Node *par = target->up;
    Node *grandpa = par;
    if(familyCase(target) || grandCase(target,par))
        return 1;
    else return 0;
}

void prune(Node *target,int round)
{
    if(target->left != NULL || target->right != NULL)
        return;
    if(target->left == NULL && target->right == NULL && isBadLeaf(target)){
        // make changes
        Node *toCut;
        toCut = target;
        toCut->data = (-1)*round;
        target = target->up;
        target->left = target->right = NULL;
        prune(target,round+1);
    }
}

void toLeaf(Node *root)
{
    if(root == NULL)
        return;
    else if(root->left == NULL && root->right == NULL){
        prune(root,1);
        return;
    }
    else{
        toLeaf(root->left);
        toLeaf(root->right);
    }
    return;
}

void freeTree(Node *root)
{
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
    return;
}

int main()
{
    Node *root;
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++){
        Node *new = malloc(sizeof(Node));
        new->left = new->right = NULL;
        scanf("%d",&new->data);
        tree[i] = new;
    }
    for(int i = 1; i <= n; i ++){
        scanf("%d",&parent[i]);
        if(parent[i] != 0)
            scanf("%c",&place[i]);
        else place[i] = 'N';
    }
    // make node connections
    int rootid;
    Node *cur,*par;
    for(int i = 1; i <= n; i ++){
        cur = tree[i];
        //cur->left = cur->right = NULL;
        if(parent[i] == 0){
            rootid = i;
            continue;
        }
        par = tree[parent[i]];
        if(place[i] == 'L'){
            par->left = cur;
        }
        else {
            par->right = cur;
        }
        cur->up = par;
    }
    
    //printf("%d\n",rootid);
    cur = tree[rootid];
    /*
    traversal(cur);
    printf("\n");*/

    // to the leaf
    toLeaf(cur);
    int i;
    for(i = 1; i < n; i ++){
        cur = tree[i];
        printf("%d ",cur->data);
    }
    cur = tree[i];
    printf("%d",cur->data);
    printf("\n");
    cur = tree[rootid];
    freeTree(cur);
    
    return 0;
}