#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
    struct _node *prev;
    char data;
    struct _node *next;
}node;

node* head;
node* rear;
node* cur_node;
node* pre_node;
node* nex_node;
int i;

void traversal()
{
    // traversal
    cur_node = head->next;
    while(cur_node->data != 0){
        printf("%c ",cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}

void insert(char input)
{
    node* temp = malloc(sizeof(node));
    temp->data = input;
    if(i == 0){
        head = cur_node;
    }
    cur_node->next = temp;
    temp->prev = cur_node;
    cur_node = temp;
    cur_node->prev = pre_node;

    cur_node->next = nex_node;
    nex_node->prev = cur_node;

    nex_node->next = rear;
    rear->prev = nex_node;
    //free(temp);
}

void remove_node()
{
    node* temp = malloc(sizeof(node));
    temp = cur_node;
    pre_node->next = nex_node;
    nex_node->prev = pre_node;
    // free(temp);
    cur_node = nex_node;
    nex_node = cur_node->next;
    return;
}
void move_left()
{
    nex_node = cur_node;
    cur_node = cur_node->prev;
    pre_node = cur_node->prev;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {

        head = malloc(sizeof(node));
        rear = malloc(sizeof(node));
        cur_node = malloc(sizeof(node));
        pre_node = malloc(sizeof(node));
        nex_node = malloc(sizeof(node));

        nex_node->data = 0;
        rear->data = 0;

        int n;
        scanf("%d",&n);

        char input;
        for(i = 0; i < n; i ++){
            scanf(" %c",&input);
            if(input == 'B')
                remove_node();
            else if(input == 'L')
                move_left();
            else
                insert(input);
            //traversal();
        }
        traversal();
    }
    
    return 0;
}