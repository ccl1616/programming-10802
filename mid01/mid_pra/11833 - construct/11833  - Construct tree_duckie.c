#include <stdlib.h>
#include <stdio.h>
// 11833 - Construct a binary tree 
// duckie
typedef struct _node {
    int value;
    struct _node *left;
    struct _node *right;
} Node;
int *inorder, *preorder, *map,*store;
int dir = -1;
Node *create_node(int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
/*
void postorder(Node *root){
    if(root->left != NULL)
        postorder(root->left);
    if(root->right != NULL)
        postorder(root->right);
    printf("%d ", root->value);
    return;
}*/
void postorder(Node *root)
{
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->value);
    return;
}
void destroy(Node* root)
{
    if(root->left != NULL)
        destroy(root->left);
    if(root->right != NULL)
        destroy(root->right);
    free(root);
    return;
}
Node *build(int inorder_start, int inorder_end)
{
    dir++;
    int position = map[dir];
    //printf("dir : %d,pos : %d\n", dir, position);
    Node *root = create_node(preorder[dir]);
    if(inorder_start == inorder_end)
        return root;
    if(inorder_start <= position - 1)
        root->left  = build(inorder_start, position - 1);
    if(inorder_end >= position + 1)
        root->right = build(position + 1, inorder_end);
    return root;
}
int main()
{
    int nums;
    scanf("%d", &nums);
    inorder = (int*)malloc(sizeof(int) * nums);
    preorder = (int*)malloc(sizeof(int) * nums);
    map = (int *)malloc(sizeof(int) * nums);
    store = (int *)malloc(sizeof(int) * nums);
    for (int i = 0; i < nums;i++){
        scanf("%d", &inorder[i]);
        store[inorder[i]] = i;
    }
    for (int i = 0; i < nums;i++){
        scanf("%d", &preorder[i]);
        map[i] = store[preorder[i]];
    }
    Node *tree = build(0, nums - 1);
    postorder(tree);
    printf("\n");
    destroy(tree);
    return 0;
}