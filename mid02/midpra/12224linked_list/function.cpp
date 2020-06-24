#include <iostream>
#include <stdexcept>
#include "function.h"
using namespace std;

void List::InsertHead(int data)
{
    ListNode* newnode = new ListNode(data);
    
    if(cnt == 0){
        head = tail = newnode;
    }
    else{
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }

    // renew cnt&pos
    cnt++;
    if(cnt == 1){
        pos = 0; // one node, no middle
        return;
    }
    else if(cnt == 2){
        middle = tail;
        pos = 2;
    }
    
    else{
        if(pos == cnt/2+1)
            middle = middle->prev;
        pos = cnt/2+1;
    }
    
}

int  List::RemoveHead()
{
    // renew cnt&pos
    // inplement throw if NULL list
    // return the data that had been delete

    int ans = 0;
    if(head == NULL)
        throw out_of_range("list is empty");
    else{
        ListNode* temp = head;
        ans = temp->data;
        if(cnt == 1){
            head = tail = NULL;
            delete temp;
            cnt = 0;
            pos = 0;
            return ans;
        }
        temp->next->prev = NULL;
        head = temp->next;
        delete temp;

        cnt--;
        if(cnt == 1){
            pos = 0;
            return ans;
        }
        else if(pos == cnt/2+1)
            middle = middle->next;
        pos = cnt/2+1;
    }
    return ans;

}

void List::InsertTail(int data)
{
    ListNode* newnode = new ListNode(data);
    if(cnt == 0){
        head = tail = newnode;
    }
    else {
        newnode->prev = tail;
        tail->next = newnode;
        tail = newnode;
    }
    
    // renew cnt&pos
    cnt++;
    if(cnt == 1){
        pos = 0; // one node, no middle
        return;
    }
    else if(cnt == 2){
        middle = tail;
        pos = 2;
    }
    else{
        if(pos != cnt/2+1)
            middle = middle->next;
        pos = cnt/2+1;
    }
}

int  List::RemoveTail()
{
    int ans = 0;
    if(head == NULL)
        throw out_of_range("list is empty");
    else{
        ListNode* temp = tail;
        ans = temp->data;
        if(cnt == 1){
            head = tail = NULL;
            delete temp;
            cnt = 0;
            pos = 0;
            return ans;
        }
        temp->prev->next = NULL;
        tail = temp->prev;
        delete temp;

        cnt--;
        if(cnt == 1){
            pos = 0;
            return ans;
        }
        else if(pos != cnt/2+1)
            middle = middle->prev;
        pos = cnt/2+1;
    }
    return ans;
}

void List::Swap()
{
    if(cnt <= 1)
        return; //!
    ListNode* oldh = head;
    ListNode* oldm = middle;
    ListNode* oldt = tail;

    tail->next = head;
    head->prev = tail;
    tail = middle->prev;
    head = middle;
    
    tail->next = NULL;
    head->prev = NULL;
    
    if(cnt % 2)
        middle = oldt;
    else middle = oldh;
}

int  List::getSize()
{
    return cnt;
}

int  List::getMiddle()
{
    return middle->data;
}