#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// 12720 - Binary search trees II: pruning
#define MIN(a,b) (a < b ? a : b)
int min = INT_MAX;
int max = -1;

typedef struct _Node{
    struct _Node* left, *right, *up;
    int value;
    int nmin, nmax;
}Node;

void traversal(Node *root, int dir)
{
    if(root != NULL){
        if(dir == 1){
            root->nmin = root->up->nmin;
            root->nmax = root->up->value;
        }
        else if(!dir){
            root->nmin = root->up->value;
            root->nmax = root->up->nmax;
        }
        traversal(root->left,1);
        traversal(root->right,0);
    }
    return;
}

void prune(Node *root)
{
    if(root == NULL)
        return;
    if(root->left == NULL && root->right ==NULL){
        root->value = -1;
    }
    else if(root->left != NULL && root->right != NULL ){
        prune(root->left);
        prune(root->right);
        root->value = MIN(root->left->value,root->right->value) -1;
    }
    else if(root->right == NULL){
        prune(root->left);
        root->value = root->left->value -1;
    }
    else if(root->left == NULL){
        prune(root->right);
        root->value = root->right->value -1;
    }
    return;
}

// left : dir = 1 , right = 0
void check(Node *root,int dir)
{
    if(root == NULL)
        return;

    // root case
    if(root->up == NULL){
        check(root->left,1);
        check(root->right,0);
    }
    // else
    else if(root != NULL && root->up != NULL){
        if(dir){
            if(root->nmin <= root->value && root->value < root->nmax){
                check(root->left,1);
                check(root->right,0);
            }
            else prune(root);
        }
        else{
            if(root->nmin < root->value && root->value <= root->nmax){
                check(root->left,1);
                check(root->right,0);
            }
            else prune(root);
        }
    }
}

int main()
{
    int n,val;
    char c;
    scanf("%d",&n);
    Node* root;
    Node* array = (Node*)malloc((n+1)*sizeof(Node));
    for(int i = 1 ;i <= n; i ++){
        scanf("%d",&val);
        if(val < min)
            min = val;
        if(val > max)
            max = val;
        (array+i)->value = val;
        (array+i)->left = (array+i)->right = NULL;
        (array+i)-> up = NULL;
    }
    for(int i = 1; i <= n; i ++){
        scanf("%d",&val);
        if(val == 0){
            (array+i)->up = NULL;
            root = array+i;
        }
        else{
            scanf(" %c",&c);
            if(c == 'R'){
                (array+val)->right = array+i;
                (array+i)->up = (array+val);
            }
            else {
                (array+val)->left = array+i;
                (array+i)->up = (array+val);
            }
        }
    }
    
    root->nmin = min;
    root->nmax = max;
    traversal(root->left,1);
    traversal(root->right,0);
    check(root,-1);
    Node *temp;
    int i;
    for(i = 1; i < n; i ++){
        temp = array+i;
        printf("%d ",temp->value);
    }
    temp = array+i;
    printf("%d\n",temp->value);
    return 0;
}
