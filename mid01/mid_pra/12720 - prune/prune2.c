#include <stdio.h>
#include <stdlib.h>
// 12720 - Binary search trees II: pruning
#define MIN(a,b) (a < b ? a : b)

typedef struct _Node{
    struct _Node* left, *right, *up;
    int value;
    int isleaf; // 1=is leaf
    int min, max;
}Node;

void traversal(Node *root)
{
    if(root != NULL){
        printf("%d ",root->value);
        traversal(root->left);
        traversal(root->right);
    }
    return;
}

int min = INT32_MAX;
int max = -1;
int turn = 1;
void destroy(Node *root)
{
    if(root == NULL)
        return;
    printf("%d\n",root->value);
    if(root->left == NULL && root->right == NULL){
        root->isleaf = 1;
        root->value = (-1)*(turn++);
        return;
    }
    else if(root->left == NULL || root->right == NULL){
        if(root->left == NULL){
            destroy(root->right);
            root->value = root->right->value-1;
        }
        else {
            destroy(root->left);
            root->value = root->left->value-1;
        }
    }
    else {
        destroy(root->left);
        destroy(root->right);
        root->value = MIN(root->left->value,root->right->value)-1;
    }
    return;
}


void prune(Node *root)
{
    if(root == NULL)
        return;
    printf("root : %d\n",root->value);
    if(root->left == NULL && root->right == NULL){
        root->isleaf = 1;
        root->value = (-1);
        return;
    }
    else if(root->left != NULL && root->right != NULL){
        destroy(root->left);
        destroy(root->right);
        root->value = MIN(root->left->value,root->right->value)-1;
    }
    else if(root->left == NULL || root->right == NULL){
        if(root->left == NULL){
            destroy(root->right);
            root->value = root->right->value-1;
        }
        if(root->right == NULL){
            destroy(root->left);
            root->value = root->left->value-1;
        }
    }
    return;
}

// dir = 1 :: left
// dir = 0 :: right
void checkNode(Node *root,int dir)
{
    if(root == NULL)
        return;
    printf("%d\n",root->value);
    if(root->up == NULL){
        checkNode(root->left,1);
        checkNode(root->right,0);
    }
    if(root->left == NULL && root->right == NULL){
        if(dir){
            if(min <= root->value && root->value < root->up->value)
                return;
            else prune(root);
        }
        else{
            if(root->up->value < root->value && root->value <= max)
                return;
            else prune(root);
        }
    }
    else{
        if(dir){
            if(min < root->value && root->value < root->up->value){
                printf("case left correct\n");
                checkNode(root->left,1);
                checkNode(root->right,0);
            }
            else {
                printf("case left wrong\n");
                prune(root);
                //checkNode(root,1);
            }
        }
        else{
            if(root->up->value < root->value && root->value < max){
                printf("case right correct\n");
                checkNode(root->left,1);
                checkNode(root->right,0);
            }
            else {
                printf("case right wrong\n");
                prune(root);
                //checkNode(root,0);
            }
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
            root = array+i;
            root->max = max;
            root->min = min;
            root->up = NULL;
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
    traversal(root);
    printf("start traversal\n");
    checkNode(root,0);
    traversal(root);
    printf("\n");
    //printf("%d %d\n",max,min);
    return 0;
}
