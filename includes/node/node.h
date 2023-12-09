#ifndef NODE_H 
#define NODE_H

#include <iostream>

using namespace std; 
template <class T> 
struct node{
    T _item; 
    node<T>* _next; 
    node<T>* _prev; 
    //using reference b/c we want to pass by reference, not copy --> too expensive
    node(const T& item = T(), node<T>* next = NULL, node<T>* prev = NULL) : _item(item), _next(next), _prev(next){}
    friend ostream& operator <<(ostream& outs, const node<T>& printMe){
        outs<< "["<<printMe._item<<"]"; 
        return outs; 
    }
}; 

#endif 