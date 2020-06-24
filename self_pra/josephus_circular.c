#include <stdio.h>
#include <stdlib.h>
// circular linked list josephus problem
typedef struct _node{
    int data;
    struct _node *next;
}node;

node* head;
node* prev;
node* temp;
int num,m;

void kill(int alive){
    // temp = malloc(sizeof(node));
    node* prev = malloc(sizeof(node));
    node* current = malloc(sizeof(node));
    current = head;
    while(alive != 1){
        for(int i = 1; i < m; i ++){
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        current = prev->next;
        alive --;
    }
    printf("%d\n",current->data);
    return;
}
int main()
{
    node* temp = malloc(sizeof(node));
    while( scanf("%d %d",&num,&m)!=EOF){
        int alive = num;
        // make list
        for(int i = 0; i < num; i++){
            node* temp = malloc(sizeof(node));
            temp->data = i+1;
            if(i == 0){
                head = temp;
                prev = temp;
            }
            else{
                prev->next = temp;
                prev = temp;
            }
        }
        prev->next = head;
        
        kill(alive);
    }
    return 0;
}