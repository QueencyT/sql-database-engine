#ifndef LINKED_LISTS_H 
#define LINKED_LISTS_H
#include "assert.h"
#include "../../includes/node/node.h"

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head){
    node<T>* nodeWalker = head; 
    while(nodeWalker != NULL){
        cout<<*nodeWalker; 
        nodeWalker = nodeWalker->_next;
    }
    cout<<endl; 
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){
    
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    node<T>* nodeWalker = head; 
    while(nodeWalker != NULL){
        if(nodeWalker->_item == key){ 
            return nodeWalker; 
        }
        nodeWalker = nodeWalker->_next; 
    }
    return NULL; //if not found
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    return prev_to_this->_prev; 
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    //item, next, prev
    if(head == NULL){ //If list empty
        head = new node<T>(insert_this, NULL, NULL); 
        return head; 
    }

    node<T>* newHead = new node<T>(insert_this, head, NULL); 
    head->_prev = newHead; 
    head = newHead;
    return newHead; //assuming we're returning the newhead
}

//don't forget to consider empty lists? and inserting head? 

//insert after ptr: insert head if marker null --> if empty
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    if(after_this == NULL || head == NULL){//if list empty insert at head 
        return _insert_head(head, insert_this); 
    }

    node<T>* insertNode = new node<T>(insert_this, after_this->_next ,after_this); 
    node<T>* nextNextNode = after_this->_next; 
    after_this->_next = insertNode; 

    if(nextNextNode != NULL){//to take care of inserting end case
        nextNextNode->_prev = insertNode; 
    }

    return insertNode; //assuming we are returning inserted node 
}

//insert before ptr: insert head if marker null --> if empty
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
    if(before_this == head || head == NULL){ //if empty, insert head
        return _insert_head(head, insert_this); 
    }
    node<T>* insertNode = new node<T>(insert_this, before_this, before_this->_prev); 
    node<T>* beforeNode = before_this->_prev; 
    beforeNode->_next = insertNode; 
    before_this->_prev = insertNode; 
    return insertNode; //assuming we are returning insertedNode 
}

//delete, return item
//what if head? // what if end? //what if empty? 
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    assert(head != NULL); //if empty, don't run
    T deletedItem = delete_this->_item; 
    if(delete_this == head){ //deleting at beginning --> need this
        node<T>* newHead = delete_this->_next; 
        delete head; 
        head = newHead; 
        return deletedItem; 
    }

    node<T>* prevNode = delete_this->_prev; 
    node<T>* nextNode = delete_this->_next; 
    prevNode->_next = nextNode; 

    if(nextNode != NULL){ //should handle deleting at end case
        nextNode->_prev = prevNode; 
    }

    delete delete_this; 
    return deletedItem; 
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    node<T>* nodeWalker = head; 
    node<T>* newHead = NULL; 
    node<T>* insertedHere = NULL; 

    if(head == nullptr){
        return nullptr; 
    }

    while(nodeWalker != NULL){
        insertedHere = _insert_after(newHead, insertedHere, nodeWalker->_item); 
        nodeWalker = nodeWalker->_next; 
    }
    return newHead; 
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
//assuming dest os destHead, and src is srcHead 
//assumng dest is null 

template <typename T>
node<T> *_copy_list(node<T> *&destHead, node<T> *srcHead){
    node<T>* srcWalker = srcHead; 
    node<T>* destWalker = NULL; 

    if(srcHead == nullptr){ //for empty case?
        destHead = nullptr; 
        return destHead; 
    }
    
    while(srcWalker != NULL){
        destWalker = _insert_after(destHead, destWalker, srcWalker->_item); 
        srcWalker = srcWalker->_next; 
    }

    //cout<<"destWalker: "<<destWalker->_item<<endl; 
    return destWalker; //WAS SRCWALKER BEFORE
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    node<T>* nodeWalker = head; 
    node<T>* temp; 

    while(nodeWalker != NULL){
        temp = nodeWalker->_next; 
        delete nodeWalker; 
        nodeWalker = temp; 
    }
    head = nullptr; 
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){ //assuming pos indexed from 0?
    node<T>* nodeWalker = head; 
    for(int i = 0; i < pos; i++){
        nodeWalker = nodeWalker->_next; 
    }
    return nodeWalker->_item; 
}

#endif