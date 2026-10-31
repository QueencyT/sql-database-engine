#ifndef STACK_H 
#define STACK_H 
#include <stdexcept>
#include "assert.h"
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;//give access to list to access _ptr
        Iterator(){
            _ptr = nullptr;
        }//default ctor

        Iterator(node<ITEM_TYPE>* p){
            _ptr = p; 
        }      
        //Point Iterator to where
        //p is pointing to

        ITEM_TYPE operator *(){
            if(_ptr == nullptr)
                throw std::runtime_error("Cannot dereference null iterator");
            return _ptr->_item; 
        }    
        //dereference operator

        bool is_null(){
            return _ptr == nullptr;
        }            //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right){
            return (left._ptr != right._ptr);
        }
        //true if left != right

        friend bool operator ==(const Iterator& left, const Iterator& right){
            return (left._ptr == right._ptr); 
        }
        //true if left == right

        Iterator& operator++(){ 
            assert(!is_null()); 
            _ptr = _ptr->_next;
            return *this;                        
        }
        //member operator:++it
        // or ++it = new_value

        friend Iterator operator++(Iterator& it, int unused){        //friend operator: it++
            assert(it._ptr!=NULL);
            Iterator returnIter = Iterator(it._ptr); 
            it._ptr = it._ptr->_next; 
            return returnIter; 
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();

    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe);
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const; 

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(){
    _top = NULL; 
    _size = 0; 
}

//BIG THREE
//copy ctor -> so assuming already empty
template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe){
    _top = NULL; 
    _copy_list(_top, copyMe._top); 
    _size = copyMe._size; 
}

//destructor
template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack(){
    _clear_list(_top); 
    _top = nullptr; 
    _size = 0; 
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator =(const Stack<ITEM_TYPE>& RHS){
    if(this == &RHS){
        return *this;
    }
    _clear_list(_top); //must do clear list
    _top = nullptr; 
    _copy_list(_top, RHS._top); 
    _size = RHS._size; 
    return *this; 
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top(){
    if(empty())
        throw std::underflow_error("Stack is empty. No top element.");
    return _top->_item; 
}

template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty(){
    return (_top == nullptr); 
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item){
    _top = _insert_head(_top, item); 
    _size++; 
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop(){
    if(empty())
        throw std::underflow_error("Stack is empty. Cannot pop.");
    ITEM_TYPE deletedItem = _delete_node(_top, _top); 
    _size--; 
    return deletedItem; 
}

template <typename T>
ostream& operator<<(ostream& outs, const Stack<T>& printMe){
    _print_list(printMe._top); 
    return outs; 
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const{
    Iterator topIter = Iterator(_top); 
    return topIter; 
}//Iterator to the head node

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const{
    Iterator nullIter; 
    return nullIter; 
}                  
//Iterator to NULL

template <typename ITEM_TYPE>
int Stack<ITEM_TYPE>::size() const { 
    return _size; 
}

#endif