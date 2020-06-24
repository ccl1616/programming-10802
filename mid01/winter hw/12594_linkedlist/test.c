#include <stdio.h>
#include <stdlib.h>
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
        current = 0;
        return;
    }
}

void SwapElementByIdx(Node** head, int idx1, int idx2)
{
    /*
    Node* previous = 0;
    Node* current = *head;
    Node* next;
    int pos = 0;
    while(current != 0 && pos != idx1){
        previous = current;
        current = current->next;
        pos ++;
    }
    if(current->next != NULL)
        next = current->next;
    else next = NULL;

    Node* previous2 = 0;
    Node* current2 = *head;
    Node* next2;
    pos = 0;
    while(current2 != 0 && pos != idx2){
        previous2 = current2;
        current2 = current2->next;
        pos ++;
    }
    if(current2->next != NULL)
        next2 = current2->next;
    else next2 = NULL;

    if(idx1 != 0){
        previous->next = current2;
        current2->next = next;
    }
    else {
        current2->next = (*head)->next;
    }
    previous2->next = current;
    current->next = next2;*/

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

void traversal(Node* head){
    if(head == NULL)
        return;
    while(head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }printf("\n");
}

int main()
{
    Node* head = NULL;
    int t,M ;
    scanf("%d %d",&t,&M);

    int *array = (int*)malloc(sizeof(int)*M);
    for(int i = 0; i < M; i++)
        scanf("%d",&array[i]);
    
    // create list
    head = createList(array, M);
    traversal(head);
    
    while(t --){
        int temp;
        int val;
        scanf("%d",&temp);
        if(temp == 0){
            // push front
            scanf("%d",&val);
            push_front(&head, val);
        }
        else if(temp == 1){
            // copy
            Node* otherHead = copyList(head);
            head = otherHead;
        }
        else if(temp == 2){
            // delete sth
            scanf("%d",&val);
            deleteElementByIdx(&head, val);
        }
        else if(temp == 3){
            // swap
            int idx1,idx2;
            scanf("%d%d",&idx1, &idx2);
            SwapElementByIdx(&head,idx1,idx2);
        }
        traversal(head);
    }

    return 0;
}