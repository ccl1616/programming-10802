#include<iostream>
#include<string.h>
#include<stdlib.h>
#include "function.h"
using namespace std;

List_stack::List_stack()
{
    this->head = this->tail = NULL;
}
List_stack::~List_stack()
{ }


void List_stack::push(const int &num)
{
    ListNode *temp = new ListNode(num);
    temp->prevPtr = this->tail;
    this->tail = temp;
}
void List_stack::pop()
{
    if(this->tail == NULL) return ; //!!
    ListNode *temp= this->tail;
    this->tail = temp->prevPtr;
    delete temp;

}
void List_stack::print()
{
    if(this->tail == NULL) return;
    ListNode *temp = this->tail;
    while(temp != NULL){
        if(temp->prevPtr == NULL){
            cout << temp->data ;
            return;
        }
        else {
            cout << temp->data << " ";
            temp = temp->prevPtr;
        }
    }
}