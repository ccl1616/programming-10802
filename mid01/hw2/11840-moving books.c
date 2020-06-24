#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 11840 - Moving books 
#define max_size 26
int book_place[max_size]; // recording which table the book is on

typedef struct _node{
    int id;
    int istable; // if this is a table node, mark as 1, else 0
    struct _node* next;
    struct _node* prev;
    struct _node* right;
}Node;

void change_log(int a,int b)
{
    // record where is this book now
    // change the table of the moving book
    book_place[a] = book_place[b]; 
}
Node* find(Node* dummy,int id,int t)
{
    Node* head = dummy;
    head = head->right;
    int i = 0;
    
    if(t == -1){
        // t = -1, means finding book
        // first find its table
        while(i != book_place[id]){
            head = head->right;
            i ++;
        }
        // go up for things on table
        head = head->next;
        while(head->id != id && head != NULL)
            head = head->next;
        return head;
    }
    else {
        // id = -1, t = x, means find a table
        while(i != t){
            head = head->right;
            i ++;
        }
        return head;
    }
}
void traversal_book(Node* firstbook)
{
    Node* cur = firstbook; 
    while(cur != NULL){
        printf(" %d",cur->id);
        cur = cur->next;
    }
}
void traversal_table(Node* dummy)
{
    Node* head = dummy;
    head = head->right;
    while(head != NULL ){
        printf("%d:",head->id);
        if(head->next != NULL)
            traversal_book(head->next);
        printf("\n");
        head = head->right;
    }
}
void Move(Node* a,Node* b)
{
    Node* mov = a;
    Node* tar = b;
    mov->prev->next = NULL;
    mov->prev = tar;
    tar->next = mov;
    change_log(a->id,b->id); //!!change "mov book"'s table to "tar book"'s table
}
void returnbook(Node* x,Node* dummy)
{
    // all the books above base should be returned
    Node* base = x;
    Node* cur;
    Node* mov = base;
    Node* tar;
    while(mov->next != NULL){
        mov = mov->next;
    }
    while(mov != base){
        cur = mov->prev;
        // get the table
        tar = find(dummy,-1,mov->id); 
        // get the top book of this table
        while(tar->next != NULL)
            tar = tar->next;
        // connect to the moving book
        tar->next = mov;
        mov->prev = tar;
        mov->next = NULL;
        cur->next = NULL;
        //change_log(mov->id,tar->id); !!RE
        book_place[mov->id] = mov->id; //!!

        mov = cur;
        cur = cur->prev;
    }
}

int main()
{
    Node* dummy = malloc(sizeof(Node));
    Node* mov;
    Node* tar;
    Node* temp; //= malloc(sizeof(Node));
    mov = dummy;

    int n;
    char str1[max_size];
    char str2[max_size];
    int a,b;
    char end[5] = "exit";
    scanf("%d",&n);

    // make original tables and books
    for(int i = 0; i < n; i ++){
        Node* new = malloc(sizeof(Node));
        Node* book = malloc(sizeof(Node));
        new->istable = 1;
        new->id = i;
        new->right = NULL;

        book_place[i] = i;
        book->id = i;
        new->next = book;
        book->next = NULL;
        book->prev = new;
        
        mov->right = new;
        mov = new;
    }
    
    // implementation
    while(scanf("%s",str1) != EOF){
        if(!strcmp(str1,end))
            break;
        scanf("%d %s %d",&a,str2,&b);
        if(a == b) continue;
        else if(book_place[a] == book_place[b]) continue; //!! 兩本書如果在同桌也不用動作

        mov = find(dummy,a,-1);
        tar = find(dummy,b,-1);
        if(str1[0] == 'm'){
            if(str2[1] == 'n'){
                // move onto
                // return books above A,B
                if(mov->next != NULL)
                    returnbook(mov,dummy);
                if(tar->next != NULL)
                    returnbook(tar,dummy);
            }
            else{
                // move over
                // return book above A
                if(mov->next != NULL)
                    returnbook(mov,dummy);
                while(tar->next != NULL)
                    tar = tar->next;
            }
        }
        else{
            if(str1[0] == 'p'){
                if(str2[1] == 'n'){
                    // pile onto
                    // !!change log for piled books
                    temp = mov;
                    while(temp->next != NULL){
                        temp = temp->next;
                        change_log(temp->id,tar->id);
                    }
                    change_log(temp->id,tar->id);
                    // return book above B
                    if(tar->next != NULL)
                        returnbook(tar,dummy);
                }
                else {
                    // pile over
                    // !!
                    temp = mov;
                    while(temp->next != NULL){
                        temp = temp->next;
                        change_log(temp->id,tar->id);
                    }
                    change_log(temp->id,tar->id);
                    // move to the last book on pile b
                    while(tar->next != NULL)
                        tar = tar->next;
                }
            }
        }
        // move node to target node
        Move(mov,tar);
    }
    traversal_table(dummy);
    
    // free memory
    mov = dummy->right;
    free(dummy);
    while(mov->right != NULL){
        Node* pre = malloc(sizeof(Node));
        pre = mov;
        while(pre->next != NULL)
            pre = pre->next;
        while(pre != mov){
            Node* temp = malloc(sizeof(Node));
            temp = pre;
            pre = pre->prev;
            free(temp);
        }
        mov = mov->right;
        free(pre);
    }
    free(mov);
    return 0;
}