#ifndef QUEUE_H 
#define QUEUE_H 
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"
#include "assert.h"

using namespace std; 

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(){
            _ptr = nullptr;
        }   
                               //default ctor
        Iterator(node<T>* p){
            _ptr = p; 
        }                   
        //Point Iterator to where
        //  p is pointing to

        T operator *(){
            return _ptr->_item; 
        }    
        //dereference operator

        bool is_null(){
            return (_ptr == NULL); 
        }            
        //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right){
            return (left._ptr != right._ptr); 
        }
        //true if left != right

        friend bool operator ==(const Iterator& left, const Iterator& right){
            return(left._ptr == right._ptr); 
        }
        //true if left == right

        Iterator& operator++(){ //member operator:++it // or ++it = new_value
            //assuming _ptr != null --> but what if null
            //assert(_ptr != NULL); 
            _ptr = _ptr->_next; 
            return *this; 
        }

        friend Iterator operator++(Iterator& it, int unused){//friend operator: it++
            assert(it._ptr != NULL);
            Iterator returnIter = Iterator(it._ptr); 
            it._ptr = it._ptr->_next; 
            return returnIter; 
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();
    //BIG THREE
    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue<T>& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;                                     //Iterator to the head node
    Iterator end() const;                                       //Iterator to NULL
    void print_pointers();
    int size() const; 
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear; //last ele before null
    int _size;
};

template <typename T>
Queue<T>::Queue(){
    _front = NULL; 
    _rear = NULL; 
    _size = 0; 
}

//BIG THREE
//copy ctor
template <typename T> 
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = NULL; 
    _rear = _copy_list(_front, copyMe._front); 
    _size = copyMe._size; 
}

template <typename T> 
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if(this == &RHS){
        return *this; 
    }
    _clear_list(_front);  //must do clear list
    _front = nullptr; 
    _rear = _copy_list(_front, RHS._front); 
    _size = RHS._size; 
    return *this; //return *this
}

template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front); 
    _front = nullptr; 
    _rear = nullptr; 
    _size = 0; 
}

template <typename T>
bool Queue<T>::empty(){
    //return (_size == 0); 
    return (_front == NULL); 
    //_front == _rear does not necessarily mean list empty, means there could be one item left and they're both pointing there
}

template <typename T>
T Queue<T>::front(){
    return _front->_item; 
}

template <typename T>
T Queue<T>::back(){
    return _rear->_item; 
}


//don't forget to update rear too
template <typename T>
void Queue<T>::push(T item){
   _rear = _insert_after(_front, _rear, item);
   _size++;  
}

template <typename T>
T Queue<T>::pop(){
    _size--; 
   return _delete_node(_front, _front); 
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    Iterator frontIter = Iterator(_front); 
    return frontIter; 
}  

//Iterator to the head node
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    Iterator endIter; 
    return endIter; 
} //Iterator to NULL --> nullIter

template <typename T>
void Queue<T>::print_pointers(){
    _print_list(_front); 
}

template <typename T>
int Queue<T>::size() const { 
    return _size; 
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){
    _print_list(printMe._front); 
    return outs;
}


#endif