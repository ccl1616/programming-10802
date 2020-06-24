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

void insert(node** cur_node,char input)
{
    node* temp = malloc(sizeof(node));
    node* cur = *cur_node;
    temp->data = input;
    temp->prev = cur->prev;
    cur->prev->next = temp;
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
    
    free(temp);
}


int main()
{
    node* head;
    node* rear;
    node* cur_node;
    node* temp;
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
            if(input == 'B')
                remove_node(&cur_node);
            else if(input == 'L')
                cur_node = cur_node->prev;
                //move_left();
            else if(input == 'R')
                cur_node = cur_node->next;

            else if(input == 'H')
                cur_node = head->next;
            else if(input == 'E')
                cur_node = rear;
            
            else if(input == 'M' ){
                // nothing before case
                // 前面沒東西
                if(cur_node->prev == head)
                    continue;
                // 是尾巴
                else if(cur_node == rear){
                    cur_node = head->next;
                    continue;
                }
                node* move_h = head->next;
                node* move_t = cur_node->prev;
                cur_node->prev = head;
                head->next = cur_node;

                cur_node->next = move_h;
                move_h->prev = cur_node;

                move_t->next = rear;
                rear->prev = move_t;
               
            }
            else if(input == 'N' ){
                if(cur_node == rear || cur_node == rear->prev)
                    continue;
                
                node* move_h = cur_node->next;
                node* move_t = rear->prev;
                head->next = move_h;
                move_h->prev = head;

                move_t->next = cur_node;
                cur_node->prev = move_t;

                cur_node->next = rear;
                rear->prev = cur_node;
            }
                //move_right();
            else if( islower(input) )
                insert(&cur_node,input);
            //traversal();
        }
        //printf("%c %c\n",cur_node->data,nex_node->data);
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
    }
    return 0;
}