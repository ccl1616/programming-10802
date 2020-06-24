#include <iostream>
#include <cstdbool>
#include"function.h"

bool Color::operator < (const Color& other) const
{

    /**
     Compare the r values of the two colors.
    If the r values equal, compare the g values of the two colors.
    If the g values equal, compare the b values of the two colors.
    If all the r, g, b values are the same, the two colors are equal.
    */
    
    if(r < other.r) return true;
    else if(r > other.r) return false;
    else{
        // now r == other.r
        if(g < other.g) return true;
        else if(g > other.g) return false;
        else{
            // now g == other.g
            if(b < other.b) return true;
            else return false;
        }
    }

}

bool Color::operator > (const Color& other) const
{
    if(r > other.r) return true;
    else if(r < other.r) return false;
    else{
        if(g > other.g) return true;
        else if(g < other.g) return false;
        else{
            if(b > other.b) return true;
            else return false;
        }
    }
}

bool Color::operator == (const Color& other) const
{
    if(r != other.r || g != other.g || b != other.b)
        return false;
    else return true;
}

Color& Color::operator = (const Color& other)
{
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    return *this;
}

Node::Node()
{
    key = Color();
    value = 1;
    left = right = nullptr;
}

Node::~Node()
{
}

MultiSet_Tree::MultiSet_Tree()
{
    root = nullptr;
}

void freetree(Node* root)
{
    if(root == NULL)
        return;
    freetree(root->left);
    freetree(root->right);
    free(root);
}

MultiSet_Tree::~MultiSet_Tree()
{
    freetree(root);
}

void MultiSet_Tree::Insert(const Color& input)
{
    if(root == nullptr){
        root = new Node();
        root->key = input;
    }
    else{
        Node* ptr = root;
        Node* par = root;
        
        while(ptr != nullptr){
            if(input == ptr->key){
                ptr->value++;
                return;
            }
            else if(input < ptr->key){
                par = ptr;
                ptr = ptr->left;
            }
            else{
                par = ptr;
                ptr = ptr->right;
            }
        }
        
        if(input < par->key){
            par->left = new Node();
            par->left->key = input;
        }
        else{
            par->right = new Node();
            par->right->key = input;
        }
        
    }
}

void MultiSet_Tree::Delete(const Color& input)
{
    /*
    Case 1 - x not exist: do nothing
    Case 2 - x exists with amount    > 1: find x and decrease its amount by one
    Case 3 - x exists with amount  == 1: remove x from the tree 
        1.Node x has 2 children: replace x by the Node with the largest key among the keys less than x.
        2.Node x has 1 child: replace x by its child Node
        3.Node x has no child: replace x by NULL.
    */
    Node* ptr = root;
    Node* par = root;
    while(ptr != nullptr){
        if(ptr->key == input)
            break;
        else if(input < ptr->key){
            par = ptr;
            ptr = ptr->left;
        }
        else {
            par = ptr;
            ptr = ptr->right;
        }
    }

    // case1
    if(ptr == nullptr)  
        return;
    // case2
    else if(ptr->value > 1)
        ptr->value --;
    // case3
    else{
        Node* child;
        // 非雙子
        if(ptr->left == nullptr || ptr->right == nullptr){
            if(ptr->left == nullptr)
                child = ptr->right;
            else child = ptr->left;

            if(ptr == root)
                root = child;
            else if(ptr == par->left)
                par->left = child;
            else par->right = child;
            
            delete ptr;
        }
        // 雙子
        else{
            Node* less_large_par = ptr;
            Node* less_large = ptr->left;
            while(less_large->right != nullptr){
                less_large_par = less_large;
                less_large = less_large->right;
            }
            ptr->key = less_large->key;
            ptr->value = less_large->value;
            // !!
            if(less_large_par->left == less_large) less_large_par->left = less_large->left;
            else less_large_par->right = less_large->left; 
            free(less_large);
        }
    }
}

const int MultiSet_Tree::Search(const Color& input) const
{
    // return the value(num) of this Color
    if(root == nullptr)
        return 0;

    Node* ptr = root;
    while( ptr != nullptr ){
        if(input == ptr->key)
            return ptr->value;
        else if(input < ptr->key)
            ptr = ptr->left;
        else ptr = ptr->right;
    }
    return 0;
}