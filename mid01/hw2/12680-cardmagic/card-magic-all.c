#include<stdio.h>
#include<stdlib.h>
//12680 - Card Magic
typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;
Node* ReadOneList();
void PrintList(Node*);
void Merge(Node*, int, int);
void Cut(Node*, int, int);

Node* ReadOneList()
{
    int size;
    Node* temp = malloc(sizeof(Node));
    scanf("%d : ",&size);
    int* a = malloc(sizeof(int)*(size+1));
    temp->size = size;
    for(int i = 0; i < size; i++ ){
        scanf("%d",&a[i]);
    }
    temp->data = a;
    temp->next = NULL;
    return temp;
}

void Merge(Node* dummy, int x, int y)
{
    if(x == y) return;
    Node* mov = dummy;
    Node* mov_prev = dummy;
    Node* target = dummy;
    int i = x-1;
    int j = y;
    int totalsize;

    // 要移動到別人家的
    while(i--) //"i--" because only want to find the mov_prev node
        mov_prev = mov_prev->next; 
    mov = mov_prev->next;
    int* m = malloc(sizeof(int)*(mov->size+1));
    m = mov->data;

    
    while(j--)
        target = target->next;
    int* t = malloc(sizeof(int)*(target->size +1));
    t = target->data;

    totalsize = target->size + mov->size;
    int* new_array = malloc(sizeof(int)*(totalsize +1));

    for(int i = 0; i < target->size ; i++)
        new_array[i] = target->data[i];
    for(int i = 0; i < mov->size; i ++)
        new_array[target->size+i] = mov->data[i];

    target->data = new_array;
    target->size = totalsize;
    mov_prev->next = mov->next;
    free(t);
    free(m);
    free(mov);
}

void PrintList(Node* dummy)
{
    Node* head = dummy->next;
    while(head != NULL){
        int i;
        for(i = 0; i < head->size-1; i ++)
            printf("%d ",head->data[i] );
        printf("%d\n",head->data[i] );
        head = head->next;
    }
}

void Cut(Node* dummy, int x, int y)
{
    Node* ori = dummy;
    Node* new = malloc(sizeof(Node));
    // relink node
    while(x--)
        ori = ori->next;
    new->next = ori->next;
    ori->next = new;
    new->size = ori->size-y;
    
    int* ori_array = malloc(sizeof(int)*(ori->size)+1);
    ori_array = ori->data;
    int* new_array = malloc(sizeof(int)*new->size+1);
    int* old_stack_new = malloc(sizeof(int)*y+1);

    for(int i = 0; i < y; i ++)
        old_stack_new[i] = ori_array[i];
    for(int i = 0; i < new->size; i ++)
        new_array[i] = ori_array[y+i];
    
    ori->size = y;
    ori->data = old_stack_new;
    new->data = new_array;
    free(ori_array);
}

int main(){
    Node* dummy_head;
    Node* tail;

    dummy_head = (Node*) malloc( sizeof(Node) );
    dummy_head->data = NULL;
    dummy_head->size = -1;

    tail = dummy_head;

    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        tail->next = ReadOneList(); // return a node with data
        tail = tail->next;   
    }
    char act[10];
    int x, y;
    for(int i=0; i<M; i++){
        scanf("%s %d %d", act, &x, &y);
        if( act[0] == 'M' ){
            Merge(dummy_head, x, y);
        }
        else if(act[0] == 'e')
            break;
        
        else{
            Cut(dummy_head, x, y);
        }
        //PrintList(dummy_head);
    }
    PrintList(dummy_head);
    return 0;
}
