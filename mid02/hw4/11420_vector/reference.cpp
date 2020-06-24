#include <iostream>
#include "function.h"
using namespace std;
using namespace oj;

void Vector::pop_back()
{
	if (size() > 0) last_--;
}

void Vector::push_back(value_type val)
{
	if (size() >= capacity()) {    //don't forget to check
		size_type new_capacity = (capacity() + 1 > capacity() * 3) ? (capacity() + 1) : (capacity() * 3);
		reserve(new_capacity);
	}
	*last_ = val;
	last_++;
}

void Vector::reserve(size_type new_capacity)
{
	if (new_capacity > capacity()) {    //don't forget to check
		pointer new_begin = new value_type[new_capacity];
		for (Int i = 0; i < size(); i++)
			new_begin[i] = begin_[i];

		size_type old_size = size(); // get old size
		size_type old_capacity = capacity(); // get old capacity
		delete[] begin_; // delete begin
		begin_ = new_begin;
		last_ = begin_ + old_size;
		end_ = begin_ + new_capacity;
	}
}

Vector::~Vector()
{
	delete[] begin_;    //if don't, you will get a memory leak OuQ
}