#include <iostream>
#include <stdlib.h>
using namespace std;
#include "function.h"


Str::Str(char* input)
	:head(NULL), tail(NULL)
{
	int pos = 0;
	while( input[pos] != '\0'){
		Char* temp = new Char(input[pos]);
		if(pos == 0){
			head = temp;
			tail = temp;
		}
		else{
			tail->next = temp;
			tail = temp;
		}
		pos ++;
	}
}

Str::Str(const Str& input)
{
	int pos = 0;
	Char* copyhead = input.head; //拿一個東西把要copy過來的資料裝好
	head = new Char(copyhead->text); //先把頭做成copy的頭
	tail = head; //才能編輯tail在head上面 不然head沒東西
	copyhead = copyhead->next;
    // 再開始 接後面的部分，把東西都接在tail後面 , then we can access to it by head pointer :)
	while(copyhead != NULL){
		tail->next = new Char(copyhead->text);
		tail = tail->next;
		copyhead = copyhead->next;
	}
}

Str& Str::strInsert(const Str& s)
{
    // put a string after this tail
	Str* s2 = new Str(s);
	this->tail->next = s2->head;
	this->tail = s2->tail;
	return *this;
}