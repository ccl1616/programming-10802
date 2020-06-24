#include <iostream>
#include <string.h>
#include <math.h>
#include "function.h"
using namespace std;

Array_BST::Array_BST()
    :BST()
{
    for(int i = 0; i < 1025; i ++)
        array[i] = 0;
}

void Array_BST::insert(const int & num)
{
    if( height() == 0){
        Height ++;
        array[1] = num;
    }
    else{
        // filter out the case that the num already exist in tree! imp!
        if(search(num) == true)
            return;
        int i = 1;
        int temp_height = 1;

        while(array[i] != 0){
            if(num < array[i])
                i = 2*i;
            else i = 2*i + 1;
            temp_height ++;
        }
        array[i] = num;

        if(temp_height > Height)
            Height = temp_height;
    }
}

bool Array_BST::search(const int & num) const
{
    int k = pow(2, height());
    for (int i = 1; i <= k-1; i++) {
        if(array[i] == num)
            return true;
    }
    return false;
}

List_BST::List_BST()
    :BST()
{
    root = NULL;
}

void List_BST::insert(const int & num)
{
    if(height() == 0){
        Height ++;
        root = createLeaf(num);
    }
    else{
        // filter out the case that the num already exist in tree! imp!
        if(search(num) == true)
            return;
        ListNode *ptr = root;
        ListNode *prev = root; //must!

        int temp_height = 1;
        while(ptr != NULL){
            if(num < ptr->key){
                prev = ptr;
                ptr = ptr->left;
            }
            else{
                prev = ptr;
                ptr = ptr->right;
            }
            temp_height ++;
        }
        if(num < prev->key)
            prev->left = createLeaf(num);
        else prev->right = createLeaf(num);
        
        if(temp_height > Height)
            Height = temp_height;
    }
}

bool List_BST::search(const int & num) const
{
    ListNode *ptr = root;
    while(ptr != NULL){
        if(ptr->key == num)
            return true;
        else {
            if(num < ptr->key)
                ptr = ptr->left;
            else ptr = ptr->right;
        }
    }
    return false;
}

ListNode* List_BST::createLeaf(int key) const
{
    ListNode* ans = new ListNode(key);
    return ans;
}

void List_BST::deleteTree(ListNode *root)
{
    if(root == NULL)
        return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    
}