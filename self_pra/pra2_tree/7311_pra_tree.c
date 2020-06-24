#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int id;
    struct _node* left;
    struct _node* right;
}Node;

int level[100];

Node* find(Node* root,int find_id)
{
    if(root == NULL)
        return NULL;
    else if(root->id == find_id)
        return root;
    else {
        Node* temp = find(root->left,find_id);
        return temp ?temp :find(root->right,find_id);
    }
}

Node* build(int num)
{
    Node* new = malloc(sizeof(Node));
    new->id = num;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void pre_order(Node* root)
{
    if(root != NULL){
        printf("%d ",root->id);
        pre_order(root->left);
        pre_order(root->right);
    }
    //else return;
}
void in_order(Node* root)
{
    if(root != NULL){
        in_order(root->left);
        printf("%d ",root->id);
        in_order(root->right);
    }
    //else return;
}
void post_order(Node* root)
{
    if(root != NULL){
        post_order(root->left);
        post_order(root->right);
        printf("%d ",root->id);
    }
    //else return;
}
int max(Node* root)
{
    int maxnum = 0;
    if(root == NULL)
        return 0;
    else{
        if(root->id > maxnum)
            maxnum = root->id;
        if(max(root->left) > maxnum)
            maxnum = max(root->left);
        if(max(root->right) > maxnum)
            maxnum = max(root->right);
    }
    return maxnum;
}
int main()
{
    int n,m;
    int root_id,l,r;
    // n: #of nodes
    // m: id of root
    scanf("%d %d",&n,&m);
    Node* head;
    head = build(m);
    
    for(int i = 0; i < n; i ++){
        // root_id, left child id, right child id
        scanf("%d %d %d",&root_id,&l,&r);
        Node* root = find(head,root_id);
        root->left = (l == -1) ?NULL :build(l);
        root->right = (r == -1) ?NULL :build(r);
    }
    
    /*
    pre_order(head);
    printf("\n");
    in_order(head);
    printf("\n");
    post_order(head);
    printf("\n");*/
    printf("%d\n",max(head));
    return 0;
}
