#include <stdio.h>
// using array to build stack
#define max 100
int stack[max];
int top = -1;

int isempty()
{
    if(top == -1)
        return 1;
    else return 0;
}

void push( int data )
{
    if(top+1 >= max)
        printf("stack is full\n");
    else{
        top ++;
        stack[top] = data;
    }
}

int pop()
{
    if( isempty() ){
        printf("is empty\n");
        return 0;
    }
    else{
        int data = stack[top];
        top --;
        return data;
    }
}

int main()
{
    // input
    int size, data;
    scanf("%d",&size);
    for(int i = 0; i < size; i ++){
        scanf("%d",&data);
        push(data);
    }

    // pop
    while( !isempty() )
        printf( "pop : %d\n",pop() );
    pop();

    return 0;
}