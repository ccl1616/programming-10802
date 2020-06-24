#include <iostream>
#include <string>
#include <queue>
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
    // this is wrong, dont do anything
    free(left);
    free(right);
}

MultiSet_Tree::MultiSet_Tree()
{
    root = nullptr;
}

MultiSet_Tree::~MultiSet_Tree()
{
    //this is wrong, write another function to do recursive freetree
    free(root);
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
        
        while(ptr != nullptr ){
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
            ptr = par->left;
            ptr->key = input;
        }
        else{
            par->right = new Node();
            ptr = par->right;
            ptr->key = input;
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

    int amount = Search(input);
    Node* ptr = root;
    // case1
    if( amount == 0)
        return;

    // case2
    else if( amount > 1){
        while( !(ptr->key == input) ){
            if(input < ptr->key)
                ptr = ptr->left;
            else ptr = ptr->right;
        }
        ptr->value --;
        return;
    }
    // case3 amount == 1
    // this is not so good , can be easier ; and also some special case wouldn't be included
    // need to take care of "child tree" of "less_large" !
    else{
        // first get the node
        Node* par = root;
        while( !(ptr->key == input) ){
            if(input < ptr->key){
                par = ptr;
                ptr = ptr->left;
            }
            else {
                par = ptr;
                ptr = ptr->right;
            }
        }

        // 1.沒有子
        if(ptr->left == ptr->right && ptr->left == nullptr){
            if(par->left == ptr)
                par->left = nullptr;
            else par->right = nullptr;
            free(ptr);
        }
        
        // 2. 只有單邊有子
        else if(ptr->left == nullptr || ptr->right == nullptr){
            Node* child;
            if(ptr->left == nullptr)
                child = ptr->right;
            else child = ptr->left;

            // 判ptr是在par的左子還是右子
            // 但如果ptr==root就沒差
            if(ptr == root){
                root = child;
                free(ptr);
            }
            else{
                if(ptr == par->left)
                    par->left = child;
                else par->right = child;
                free(ptr);
            }
        }
        
        // 3.雙子
        else{
            Node* less_large = ptr->left;
            Node* less_large_par = ptr->left;
            while(less_large->right != nullptr){
                less_large_par = less_large;
                less_large = less_large->right;
            }
            ptr->key = less_large->key;
            ptr->value = less_large->value;
            less_large_par->right = nullptr;
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