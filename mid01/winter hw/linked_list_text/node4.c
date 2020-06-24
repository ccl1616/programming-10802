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
node* nex_node;
//node* temp;

int i;

void traversal()
{
    // traversal
    cur_node = head;
    while(cur_node->next != NULL){
        printf("%c",cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}

void insert(char input)
{
    node* temp = malloc(sizeof(node));
    temp->data = input;
    /*
    if(i == 0){
        cur_node = head;
    }*/
    //nex_node = cur_node->next;

    cur_node->next = temp;
    temp->prev = cur_node;
    temp->next = nex_node;
    nex_node->prev = temp;

    cur_node = temp;
}

void remove_node()
{
    node* temp; // = malloc(sizeof(node));
    temp = cur_node;
    cur_node = temp->prev;
    cur_node->next = nex_node;
    nex_node->prev = cur_node;
    free(temp);
}
void move_left()
{
    //if(cur_node->prev->prev != NULL){
        cur_node = cur_node->prev;
        nex_node = nex_node->prev;
    //}
}
void move_right()
{
    cur_node = cur_node->next;
    nex_node = nex_node->next;
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
        nex_node = malloc(sizeof(node));
        
        head->prev = NULL;
        rear->next = NULL;

        head->next = rear;
        rear->prev = head;
        //rear->data = 0;

        int n;
        scanf("%d",&n);

        char input;
        scanf(" %c",&input);
        head->data = input;
        cur_node = head;
        nex_node = cur_node->next;
        nex_node->prev = cur_node;

        for(i = 1; i < n; i ++){
            scanf(" %c",&input);
            if(input == 'B')
                remove_node();
            else if(input == 'L')
                move_left();
            else if(input == 'R')
                move_right();
            else
                insert(input);
            //traversal();
        }
        //printf("%c %c\n",cur_node->data,nex_node->data);
        traversal();
    }
    /*
    free(cur_node);
    free(nex_node);
    free(rear);
    free(head);*/
    //free(temp);
    return 0;
}