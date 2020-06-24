#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 12718 - Calculator with deletion - revised
#define max_s 300005
char ops[4] = "+-*"; //0,1,2
char str[max_s];
int pos;
int i;

typedef struct _node {
    int size; // index of each node.
    long long value;
    int type; // num:-1, +:0 , -:1 , *:2 
    struct _node *left, *right, *parent;
} Node;

long long getValue(int a, int b, int op_id)
{
    a = a%10007;
    b = b%10007;
    long long ans = 0;
    if(op_id == 0)
        ans = (a+b)%10007;
    else if(op_id == 1)
        ans = (a-b)%10007;
    else if(op_id == 2)
        ans = (a*b)%10007;
    
    if(ans < 0) 
        ans += 10007; //!!
    return ans;
}

Node *buildTree(Node *cur)
{
    if(cur == NULL){
        cur = malloc(sizeof(Node));
        cur->left = cur->right = NULL;
        char c;
        c = str[pos++];
        // node is op case
        if(c == '+' || c =='-' || c == '*'){
            for(i = 0; i < 3; i ++){
                if(c == ops[i])
                    break;
            }
            cur->type = i;
            cur->left = buildTree(cur->left);
            cur->right = buildTree(cur->right);
            cur->left->parent = cur->right->parent = cur;
            cur->value = getValue(cur->left->value,cur->right->value,cur->type);
            if(cur->left->type < 0)
                cur->size += 1;
            else cur->size += cur->left->size + 1;
            if(cur->right->type < 0)
                cur->size += 1;
            else cur->size += cur->right->size + 1;
        }
        // node is number case
        else{
            cur->type = -1;
            cur->value = c-'0';
            cur->size = 0;
        }
    }
    return cur;
}

Node *findNode(int pos,Node *root)
{
    Node *target = root;
    int now = 1;
    int left_size;
    while(now != pos){
        if(target == NULL)
            break;
        left_size = target->left->size;
        if(pos > now + left_size + 1){
            target = target->right;
            now = now + left_size + 2;
        }
        else if(pos <= now + left_size + 1){
            target = target->left;
            now += 1;
        }
        else printf("wrong!\n");
    }
    return target;
}

void freeTree(Node *root)
{
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int renewSize(Node *root)
{
    int temp = 0;
    if(root->left->type >= 0)
        temp = root->left->size+1;
    else temp = 1;
    if(root->right->type >= 0)
        temp += root->right->size+1;
    else temp += 1;
    return temp;
}

// !
void changeValue(Node *target) 
{
    if(target != NULL && target->left != NULL && target->right != NULL){
        target->value = getValue(target->left->value,target->right->value,target->type);
        target->size = renewSize(target);
    }
    if(target->parent != NULL) // !
        changeValue(target->parent);
    return;
}

Node *removeNode(Node *root,Node *target,int l, int r)
{
    Node *par,*tar,*tar_r;
    tar = target;
    if(l != 1){
        tar_r = tar->right;
        par = tar->parent;
        if(par->left == tar)
            par->left = tar_r;
        else if(par->right == tar)
            par->right = tar_r;
        else printf("wrong!\n");
        tar_r->parent = par;

        target->right = NULL;
        par->size -= (r-l+1);
        changeValue(par);
    }
    // l == 1, is root
    else{
        par = tar->right;
        target->right = NULL;
        freeTree(target);
        return par;
    }
    freeTree(target);
    return root; 
}

int main()
{
    int n; // #of operations
    scanf("%d",&n);
    scanf("%s",str);
    Node *root = NULL;
    root = buildTree(root);
    root->parent = NULL;
    
    int l,r;
    char c;
    Node *target;
    while(n--){
        scanf(" %c",&c);
        if(c == 'Q'){
            scanf(" %d",&l);
            target = findNode(l,root);
            printf("%lld\n",target->value);
        }
        else{
            scanf("%d %d",&l,&r);
            target = findNode(l,root);
            root = removeNode(root,target,l,r);
        }
    }
    freeTree(root);
    return 0;
}