#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// 12669 - Another Text Editor   

typedef struct _node{
    struct _node *prev;
    char data;
    struct _node *next;
}node;

int i;
node* head;
node* rear;
node* cur_node;
node* temp;

void insert(node** cur_node,char input)
{
    node* temp = malloc(sizeof(node));
    node* cur = *cur_node;
    temp->data = input;
    cur->prev->next = temp;
    temp->prev = cur->prev;
    temp->next = cur;
    cur->prev = temp;
}

void remove_node(node** cur_node)
{
    node* temp = malloc(sizeof(node));
    node* cur = *cur_node;
    temp = cur->prev;
    temp->prev->next = cur;
    cur->prev = temp->prev;
    temp->prev = NULL;
    temp->next = NULL;
    
    free(temp);
}

void move_front_to_back()
{
    // nothing before cur
    //if(cur_node->prev == head || cur_node == head)
    if(cur_node == head->next)
        return;
    // nothing is after cur, move cur to the beginning
    else if(cur_node == rear){
        cur_node = head->next;
        return;
    }
    node* move_h = head->next;
    node* move_t = cur_node->prev;

    rear->prev->next = move_h;
    move_h->prev = rear->prev;

    head->next = cur_node;
    cur_node->prev = head;

    move_t->next = rear;
    rear->prev = move_t;
    return;
}
void move_back_to_front()
{
    // nothing is after cur
    if(cur_node == rear)
        return;
    // nothing is before cur
    else if(cur_node == head->next){
        cur_node = rear;
        return;
    }
    node* move_h = cur_node;
    node* move_t = rear->prev;

    move_h->prev->next = rear;
    rear->prev = move_h->prev;
    move_t->next = head->next;
    head->next->prev = move_t;
    move_h->prev = head;
    head->next = move_h;
    cur_node = rear;
    return;
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
        
        head->prev = NULL;
        rear->next = NULL;
        
        head->next = rear;
        rear->prev = head;
        //rear->data = 0;
        cur_node = rear;

        int n;
        scanf("%d",&n);
        char str[1000005];
        scanf("%s",str);
        char input;
        for(i = 0; i < n; i ++){
            input = str[i];
            if(input == 'B'){
                if(cur_node != head->next)
                    remove_node(&cur_node);
            }
            else if(input == 'L'){
                if(cur_node != head->next)
                    cur_node = cur_node->prev;
            }
            else if(input == 'R'){
                if(cur_node != rear)
                    cur_node = cur_node->next;
            }
            else if(input == 'H')
                cur_node = head->next;
            else if(input == 'E')
                cur_node = rear;
            else if(input == 'M' ){
                move_front_to_back();
            }
            else if(input == 'N' ){
                move_back_to_front();
            }
            else if( islower(input) )
                insert(&cur_node,input);
            //printf("%c\n",cur_node->data);
        }
        cur_node = head->next;
        while(cur_node->next != NULL){
            printf("%c",cur_node->data);
            cur_node = cur_node->next;
        }
        printf("\n");
        cur_node = head;
        while(cur_node->next != NULL){
            temp = cur_node;
            cur_node = cur_node->next;
            free(temp); 
        }
        free(rear);
        
    }
    return 0;
}