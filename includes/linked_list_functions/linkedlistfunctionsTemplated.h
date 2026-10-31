#ifndef LINKED_LISTS_H 
#define LINKED_LISTS_H
#include <cassert>
#include <stdexcept>
#include "../../includes/node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head){
    node<T>* nodeWalker = head; 
    while(nodeWalker != nullptr){
        cout<<*nodeWalker; 
        nodeWalker = nodeWalker->_next;
    }
    cout<<endl; 
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){
     if (head == nullptr) {
        return;
    }

    // Find the tail
    node<T>* current = head;

    while (current->_next != nullptr) {
        current = current->_next;
    }

    // Traverse backward
    while (current != nullptr) {
        cout << *current;
        current = current->_prev;
    }

    cout << '\n';
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    node<T>* nodeWalker = head; 
    while(nodeWalker != nullptr){
        if(nodeWalker->_item == key){ 
            return nodeWalker; 
        }
        nodeWalker = nodeWalker->_next; 
    }
    return nullptr; //if not found
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    return prev_to_this == nullptr ? nullptr : prev_to_this->_prev; 
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    //item, next, prev
    if(head == nullptr){ //If list empty
        head = new node<T>(insert_this, nullptr, nullptr); 
        return head; 
    }

    node<T>* newHead = new node<T>(insert_this, head, nullptr); 
    head->_prev = newHead; 
    head = newHead;
    return newHead; //assuming we're returning the newhead
}

//don't forget to consider empty lists? and inserting head? 

//insert after ptr: insert head if marker null --> if empty
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    if(after_this == nullptr || head == nullptr){//if list empty insert at head 
        return _insert_head(head, insert_this); 
    }

    node<T>* insertNode = new node<T>(insert_this, after_this->_next ,after_this); 
    node<T>* nextNextNode = after_this->_next; 
    after_this->_next = insertNode; 

    if(nextNextNode != nullptr){//to take care of inserting end case
        nextNextNode->_prev = insertNode; 
    }

    return insertNode; //assuming we are returning inserted node 
}

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T item) {
    if (head == nullptr || before_this == head) {
        return _insert_head(head, item);
    }

    assert(before_this != nullptr);
    node<T>* previous = before_this->_prev; //if before_this is valid, then previous should never be null
    assert(previous != nullptr);
    node<T>* newNode = new node<T>(item, before_this, previous);
    previous->_next = newNode;
    before_this->_prev = newNode;
    return newNode;
}

template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    assert(head != nullptr);
    assert(delete_this != nullptr);

    T deletedItem = delete_this->_item;

    // Deleting the head
    if (delete_this == head) {
        head = head->_next;

        if (head != nullptr) 
            head->_prev = nullptr;

        delete delete_this;
        return deletedItem;
    }

    // Deleting a middle or last node
    node<T>* prevNode = delete_this->_prev;
    node<T>* nextNode = delete_this->_next;

    prevNode->_next = nextNode;

    if (nextNode != nullptr)
        nextNode->_prev = prevNode;

    delete delete_this;
    return deletedItem;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
//assuming dest os destHead, and src is srcHead 
//assumng dest is null 

template <typename T>
node<T> *_copy_list(node<T> *&destHead, node<T> *srcHead){
    assert(destHead == nullptr);
    node<T>* srcWalker = srcHead; 
    node<T>* destWalker = nullptr; 
    
    while(srcWalker != nullptr){
        destWalker = _insert_after(destHead, destWalker, srcWalker->_item); 
        srcWalker = srcWalker->_next; 
    }
    return destWalker; 
}

template <typename T>
node<T>* _copy_list(node<T>* head) {
    node<T>* newHead = nullptr;
    _copy_list(newHead, head);
    return newHead;
}


//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    node<T>* nodeWalker = head; 
    node<T>* temp; 

    while(nodeWalker != nullptr){
        temp = nodeWalker->_next; 
        delete nodeWalker; 
        nodeWalker = temp; 
    }
    head = nullptr; 
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){ //assuming pos indexed from 0? //assuming pos is valid
    if (pos < 0)
        throw std::out_of_range("Position cannot be negative");

    node<T>* nodeWalker = head; 
    for(int i = 0; i < pos && nodeWalker; i++){
        nodeWalker = nodeWalker->_next; 
    }

    if(nodeWalker == nullptr) 
        throw std::out_of_range("Position is out of range");

    return nodeWalker->_item; 
}

#endif