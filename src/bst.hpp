#ifndef BST_HPP
#define BST_HPP
#include "sorted_list.hpp"
#include "container.h"
#include "stdexcept"
#include "array_container.hpp"
#include <exception>
#include <iostream>


///Tree leaf that is used in binary tree such as bst
template<typename T>
class leaf {
public:
    virtual ~leaf() = default;
    /// Stores value of type T
    T value;
    /// Stores right leaf
    leaf* right = nullptr;
    /// Stores left leaf
    leaf* left = nullptr;
    /// Stores parent leaf;
    leaf* parent = nullptr;
};


///Binary Search Tree with sorted_list interface. 
///It's using node like objects.
template<typename T> 
class bst : public sorted_list<T>, public container {
public:
    bst() = default;;
    ~bst();
    /// \see sorted_list
    void insert(T value) override;
    /// \see sorted_list
    T pop_front() override;
    /// \see sorted_list
    T pop_back() override;
    /// \see sorted_list
    T operator[](int index) override;
    /// \see sorted_list
    bool find(T value) override;
    /// traverses over every element and delete it from memory
    /// \see container
    bool clear() override;
    /// prints tree
    void print();


    leaf<T>* get_data(){return this->head;};
protected:
    /// Used to find leaf in tree or check if element is in tree
    /// It's recursive so curr has to be in 
    /// \param value of type T *self explanatory*
    /// \param curr pointer of current leaf to be processed
    /// \return pointer to the leaf with value or nullptr otherwise
    leaf<T>* find_leaf(leaf<T>* curr, T value);
    ///Head of the tree
    leaf<T>* head = nullptr;
    /// Recursive function for inserting a value at its spot
    /// \param curr currently processed leaf
    /// \param value
    void insert_rec(leaf<T>* curr,T value);
    /// Used to go on every element of the tree from left to right
    /// \param curr as its recursive curr means the elem that it start on the first is head
    /// \param curr_idx 
    /// \param ideal_idx
    leaf<T>* traverse(leaf<T>* curr, int* curr_idx, int ideal_idx);
    /// prints tree in linked-list way
    /// \param curr
    void print(leaf<T>* curr);
    /// Recursion func used to clear tree
    /// \param curr pointer to currently processed leaf
    /// \return true if everything go as expected
    bool clear_rec(leaf<T> *curr);
};

template<typename T>
bool bst<T>::clear(){
    if (container::size_ ==0){
        return true;
    }
    bool ret = this->clear_rec(head);
    container::size_ = 0;
    return ret;
}

template<typename T>
bool bst<T>::clear_rec(leaf<T>* curr){
    if (curr == nullptr){
        return true;
    }
    this->clear_rec(curr->left);
    curr->left = nullptr;
    this->clear_rec(curr->right);
    curr->right = nullptr;

    curr->parent = nullptr;
    delete curr;
    return true;
}

template<typename T>
void bst<T>::insert(T value)
{
    if(head == nullptr){
        head = new leaf<T>();
        head->value = value;
        container::size_=1;
    }
    else{
        insert_rec(head,value);
        container::size_ ++;
    }
}

template<typename T>
void bst<T>::insert_rec(leaf<T>* curr, T value)
{
    if (value > curr->value){
        if (curr->right == nullptr){
            curr->right = new leaf<T>();
            curr->right->value = value;
            curr->right->parent = curr;
        }
        else insert_rec(curr->right, value);
    }
    else if (value < curr->value){
        if (curr->left == nullptr){
            curr->left = new leaf<T>();
            curr->left->value = value;
            curr->left->parent = curr;
        }
        else insert_rec(curr->left, value);
    }
}

template<typename T>
T bst<T>::operator[](int index)
{
    int current_idx = 0;
    return (this->traverse(head,&current_idx,index))->value;
}

template<typename T>
T bst<T>::pop_front()
{
    T ret;
    leaf<T>* cp2 = head;
    leaf<T>* cp = nullptr;
    while (cp2->left != nullptr)
    {
        cp = cp2;
        cp2 = cp2->left;
    }
    ret = cp2 -> value;
    if (cp == nullptr){
        head = head -> right; // Means left most is root
    }
    else{
        cp -> left = cp2->right;
    }
    delete cp2;
    container::size_--;
    return ret;
}

template<typename T>
T bst<T>::pop_back()
{
    T ret;
    leaf<T>* cp2 = head;
    leaf<T>* cp = nullptr;
    while (cp2->right != nullptr)
    {
        cp = cp2;
        cp2 = cp2->right;
    }
    ret = cp2 -> value;
    if (cp == nullptr){
        head = head->left; // Means right most is root
    }
    else{
        cp -> right = cp2->left;
    }
    delete cp2;
    container::size_--;
    return ret;
}

template<typename T>
bool bst<T>::find(T value)
{
    return this->find_leaf(head,value) != nullptr;
}

template<typename T>
leaf<T>* bst<T>::find_leaf(leaf<T>* curr,T value)
{
    if (curr == nullptr)
    {
        return nullptr;
    }
    printf("%d\n",curr->value);

    if(value < curr->value){
        return this->find_leaf(curr->left,value);
    }
    else if (value > curr->value){
        return this->find_leaf(curr->right,value);
    }
    else{
        return curr;
    }
}

template<typename T>
leaf<T>* bst<T>::traverse(leaf<T>* curr, int* curr_idx, int ideal_idx)
{
    if (curr == nullptr){
        return nullptr;
    }
    auto ret = this->traverse(curr->left, curr_idx, ideal_idx);
    if(ret != nullptr){
        return ret;
    }
    *curr_idx += 1;
    if (ideal_idx == *curr_idx){
        return curr;
    }
    ret = this->traverse(curr->right, curr_idx, ideal_idx);
    if(ret != nullptr){
        return ret;
    }
    return nullptr;
}

template<typename T>
void bst<T>::print()
{
    this->print(head);
    std::cout << std::endl;
}

template<typename T>
void bst<T>::print(leaf<T>* curr){
    using namespace std;
    if(curr == nullptr){
        return;
    }
    cout << "(";
    this->print(curr->left);
    cout << curr->value << "";
    this->print(curr->right);
    cout << ")";
}

template<typename T>
bst<T>::~bst() {
    this->clear();
}

#endif

