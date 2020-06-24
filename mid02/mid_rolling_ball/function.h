#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include <iostream>
#include <queue>
using namespace std;
class Color{
    public:
        Color(){ this->r = this->g = this->b = -1; };
        Color(int x, int y, int z): r(x), g(y), b(z){};
        Color(const Color& c): r(c.r), g(c.g), b(c.b){};
        ~Color(){};
        bool operator < (const Color& other) const; //do
        bool operator > (const Color& other) const; //do
        bool operator == (const Color& other) const; //do
        Color& operator = (const Color& other); //do
        friend ostream& operator<<(ostream& os, const Color& ball);
    private:
        int r, g, b;
};

class Node{
    public:
        Node(); //do
        ~Node(); //do
    public:
        Color key;
        int value;
        Node* left;
        Node* right;
};

class MultiSet{
    public:
        MultiSet(){};
        virtual ~MultiSet(){};
        virtual void Insert(const Color&) = 0;
        virtual void Delete(const Color&) = 0;
        virtual const int Search(const Color&) const = 0;
        virtual void PrintSet() const = 0;
};

class MultiSet_Tree : public MultiSet{
    public:
        MultiSet_Tree(); //do
        virtual ~MultiSet_Tree(); //do
        virtual void Insert(const Color&); //do
        virtual void Delete(const Color&); //do
        virtual const int Search(const Color&) const; //do
        virtual void PrintSet() const;
    private:
        Node* root;
};

#endif