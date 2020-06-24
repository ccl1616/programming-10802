#include <stdio.h>
#include <stdlib.h>

// Data structure to store a Binary Tree node
typedef struct _Node
{
	int key;
	struct _Node *left, *right;
}Node;

// Function to create a new binary tree node having given key
Node* newNode(int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left = node->right = NULL;

	return node;
}

// Recursive function to perform inorder traversal of a binary tree
void inorderTraversal(Node* root)
{
	if (root == NULL)
		return;

	inorderTraversal(root->left);
	printf("%d ", root->key);
	inorderTraversal(root->right);
}

// Recursive function to perform preorder traversal of a binary tree
void preorderTraversal(Node* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->key);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void postorder(Node* root)
{
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->key);
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
// Recursive function to construct a binary tree from given
// inorder and preorder sequence
Node* construct(int inorder[], int start, int end,
				int preorder[], int *pIndex)
{
	// base case
	if (start > end)
		return NULL;

	// The next element in preorder[] will be the root node of
	// subtree formed by inorder[start, end]
	Node *node = newNode(preorder[(*pIndex)++]);

	// search the index of root node in inorder[] to determine the
	// boundary of left and right subtree
	int i;
	for (i = start; i <= end; i++) {
		if (inorder[i] == node->key)
			break;
	}
    //printf("%d ",node->key);
	// recursively construct the left subtree
    //printf("  %d\n",*pIndex);
	node->left = construct(inorder, start, i - 1, preorder, pIndex);

	// recursively construct the right subtree
	node->right = construct(inorder, i + 1, end, preorder, pIndex);

	// return current node
	return node;
}

// Construct a binary tree from inorder and preorder traversals
// This function assumes that the input is valid
// i.e. given inorder and preorder sequence forms a binary tree
Node* constructTree(int inorder[], int preorder[], int n)
{
	// pIndex stores index of next unprocessed node in preorder sequence
	int *pIndex;

	// root node is present at index 0 in preorder sequence
	pIndex = 0;

	return construct(inorder, 0, n - 1, preorder, &pIndex);
}

// main function
int main()
{
    int n;
    scanf("%d",&n);
    int* inorder = malloc(sizeof(int)*n);
    int* preorder = malloc(sizeof(int)*n);
    for(int i = 0; i < n; i ++)
        scanf("%d",&inorder[i]);
    for(int i = 0; i < n; i ++)
        scanf("%d",&preorder[i]);

	Node* root = constructTree(inorder, preorder, n);

	// traverse the constructed tree
    /*
	printf("Inorder : "); inorderTraversal(root);
	printf("\nPreorder : "); preorderTraversal(root);*/
    postorder(root);
    printf("\n");
    destroy(root);
	return 0;
}