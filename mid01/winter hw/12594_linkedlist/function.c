#include <stdio.h>
// 12594 - Implement Linked List
typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* createList(int *a, int size)
{
    Node* head;
    Node* current;
    for(int i = 0; i < size; i ++){
        Node* temp = (Node*)malloc(sizeof(Node)); //imp!
        temp -> data = a[i];
        if(i == 0){
            head = temp;
            current = temp;
        }
        else{
            current -> next = temp;
            current = temp;
        }
    }
    current -> next = NULL;
    return head;
}

void push_front(Node** head, int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp -> data = val;
    temp -> next = *head;
    *head = temp; 
}
Node* copyList(Node* head)
{
    if(head == NULL) return NULL;
    else{
        Node* clone = malloc(sizeof(Node));
        Node* current;
        Node* previous;
        clone->data = head->data;
        current = head->next;
        previous = clone;

        while(current != NULL){
            Node* temp = malloc(sizeof(Node));
            temp->data = current->data;
            temp->next = NULL;
            previous->next = temp;
            previous = temp;
            current = current->next;
        }
        return clone;        
    }
}

void deleteElementByIdx(Node** head, int idx)
{
    if(idx == 0){
        *head = (*head)->next;
        return ;
    }
    else{
        int pos = 0;
        Node* previous = 0;
        Node* current = *head;
        while(current != NULL && pos != idx){
            previous = current;
            current = current->next;
            pos ++;
        }
        if(current == NULL) return;
        previous->next = current->next;
        return;
    }
}

void SwapElementByIdx(Node** head, int idx1, int idx2)
{
    Node* node1;
    Node* node2;
    Node* current = *head;
    int found = 0;
    int pos = 0;
    while(found != 2 ){
        if(current == NULL) 
            return;
        if(pos == idx1){
            node1 = current;
            found ++;
        }
        if(pos == idx2){
            node2 = current;
            found ++;
        }
        current = current->next;
        pos ++;
    }
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}