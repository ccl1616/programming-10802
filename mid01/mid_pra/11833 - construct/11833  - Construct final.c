#include <stdlib.h>
#include <stdio.h>
// 11833 - Construct a binary tree 
// final version

// input inorder & preorder
// output postorder
typedef struct _node {
    int value;
    struct _node *left;
    struct _node *right;
}Node;

Node *create_node(int value);
void post_order(Node *root);
void destroy(Node* root);

int *inorder,*pre_order,*a,*b;
//int inorder_start,inorder_end;
int pos;
//int *pIndex;

Node *create_node(int value)
{
    Node* new = malloc(sizeof(Node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

Node *build(int inorder_start, int inorder_end)
{
    Node* root = create_node(pre_order[pos]);
    int i = b[pos];
    pos++;
    if(inorder_start == inorder_end)
        return root;
    if(inorder_start <= i-1)
        root->left = build(inorder_start,i-1);
    if(inorder_end >= i+1)
        root->right = build(i+1,inorder_end);
    return root;
}
void post_order(Node *root)
{
    if(root == NULL)
        return;
    post_order(root->left);
    post_order(root->right);
    printf("%d ",root->value);
    return;
}
void destroy(Node *tree)
{
    if(tree->left!= NULL)
        destroy(tree->left);
    if(tree->right!= NULL)
        destroy(tree->right);
    free(tree);
    return;
}
int main()
{
    int n;
    scanf("%d",&n);
    inorder = malloc(sizeof(int)*n);
    pre_order = malloc(sizeof(int)*n);
    a = malloc(sizeof(int)*n);
    b = malloc(sizeof(int)*n);

    for(int i = 0; i < n; i ++){
        scanf("%d",&inorder[i]);
        a[inorder[i]] = i;
    }
    for(int i = 0; i < n; i ++){
        scanf("%d",&pre_order[i]);
        b[i] = a[pre_order[i]];
    }
    //pIndex = 0;
    Node* tree = build(0,n-1);
    //printf("%d\n",tree->value);
    post_order(tree);
    printf("\n");
    destroy(tree);
    return 0;
}
