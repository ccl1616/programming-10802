#include<iostream>
#include<string>
#include"function.h"
using namespace oj;
using namespace std;
#define max(a,b) a > b ?a:b

void Vector::pop_back()
{
    if(size() > 0) // !!
        last_ --;
}

void Vector::push_back(value_type val)
{
    if(size() >= capacity() ){
        size_type new_cap = max(capacity()+1,capacity()*3);
        reserve(new_cap);
    }
    *last_ = val;
    last_ ++; 
}

void Vector::reserve(size_type new_capacity)
{
    if(new_capacity <= capacity())
        return;
    else {
        //make a new one by the old data but new capacity, delete old, make it current array
        pointer new_array = new value_type[new_capacity];
        for(Int i = 0; i < size(); i ++)
            new_array[i] = begin_[i];
        
        // get the size, cause the last pointer would need it, otherwise we'll lost the old size of it (# of old element)
        size_type pre_size = size();
        delete[] begin_;
        //paste the new onto old
        begin_ = new_array;

        //set up pointer
        last_ = begin_ + pre_size;
        end_ = begin_ + new_capacity;
        return;
    }
}

Vector::~Vector()
{ 
    delete[] begin_; // the "[]" is a must, cause here the begin(array) is a consecutive memory
}