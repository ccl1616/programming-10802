#include <stdio.h>
#include <stdlib.h>
typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* head;
Node* createList(int n);
void freeList();
int solveJosephus(int step);

Node* createList(int n)
{
    Node* prev_n;
    Node* head = malloc(sizeof(Node));
    
    for(int i = 0; i < n; i++){
            Node* temp = malloc(sizeof(Node));
            temp->number = i+1;
            if(i == 0){
                head = temp;
                prev_n = temp;
            }
            else{
                prev_n->next = temp;
                temp->prev = prev_n;
                prev_n = temp;
            }
    }
    prev_n->next = head;
    head->prev = prev_n;

    return head;
}

void traversal(Node** head)
{
    Node* _head = *head;
    Node* cur = *head;
    cur = cur->next;
    printf("1->");

    while(cur->number != 1){
        printf("%d->",cur->number);
        cur = cur->next;
    }
    printf("%d",cur->number);
    printf("\n");
}

int solveJosephus(int step)
{
    int dir = 1; // odd means clockwise
    Node* cur = head;

    while(cur->next!= cur && cur->prev != cur){
        Node* del;
        if(dir == 1){
            // count and kill
            for(int i = 1; i < step; i++)
                cur = cur->next;
            del = cur;
            dir = 0;
            cur = cur->prev;
        }
        else{
            for(int i = 1; i < step; i++)
                cur = cur->prev;
            del = cur;
            dir = 1;
            cur = cur->next;
        }
        del->prev->next = del->next;
        del->next->prev = del->prev;
        free(del);
    }
    head = cur;
    return head->number;
}
void freeList()
{
    free(head);
}

int main()
{
    int n, m;

    while(scanf("%d%d", &n, &m)!=EOF){
        head = createList(n);
        printf("%d\n", solveJosephus(m));
        freeList();
    }
}