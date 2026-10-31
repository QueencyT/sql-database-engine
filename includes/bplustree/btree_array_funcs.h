#ifndef BTREE_ARRAY_FUNCTIONS_H 
#define BTREE_ARRAY_FUNCTIONS_H

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std; 

template <class T>
T maximal(const T& a, const T& b){ //if a and b equal, should return b?
    if(a > b){
        return a; 
    }
    return b; 
}
//return the larger of the two items

template <class T>
void swap(T& a, T& b){
    T temp = a; 
    a = b; 
    b = temp; 
}//swap the two items

template <class T>
int index_of_maximal(T data[], int n) {
    if(n <= 0)
        throw std::invalid_argument("Array size must be greater than 0");

    int maxIndex = 0;

    for (int i = 1; i < n; i++) {
        if (data[i] > data[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}


template <class T>
void insert_item(T data[ ], int insertIndex, int& n, T entry){ //assuming at least one space
    if(insertIndex < 0 || insertIndex > n) 
        throw std::out_of_range("Insert index is out of range");

    for(int i = n; i > insertIndex; i--){
       data[i] = data[i-1]; 
    }

    data[insertIndex] = entry; 
    n++;
}//insert entry at index i in data

template <class T>
int first_ge(const T data[ ], int n, const T& entry){ //if inserting greatest, return n 
    for(int i = 0; i < n; i++){
        if(entry <= data[i]){
            return i; 
        }
    }
    return n; //else biggest so return n
}//return the first element in data that is
//return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry){//from smallest to largest I assume? //we figure out where to insert?  
    int insertIndex = first_ge(data, n, entry); 
    insert_item(data, insertIndex, n, entry); 
} 
//insert entry into the sorted array
//data with length n

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    //what if at capacity? //do we not care? 
    data[n] = entry; //insert at end
    n++; 
}//append entry to the right of data


template <class T>
void detach_item(T data[ ], int& n, T& entry){
    if(n <= 0)
        throw std::underflow_error("Cannot detach item from empty array");

    entry = data[n - 1]; 
    n--;
}//remove the last element in data and place
//it in entry


template <class T>
void delete_item(T data[], int deleteIndex, int& n, T& entry) {
    if (deleteIndex < 0 || deleteIndex >= n)
        throw std::out_of_range("Delete index is out of range");

    entry = data[deleteIndex];

    for (int i = deleteIndex; i < n - 1; i++) {
        data[i] = data[i + 1];
    }

    n--;
}//delete item at index i and place it in entry

//delete from data2 and then merge 
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
    int itemsToDelete = n2; 
    T insert;
    for(int i = 0; i < itemsToDelete; i++){
        insert = data2[i];
        insert_item(data1, n1,n1, insert); 
    }
    n2 = 0; //clear data2
} 

//append data2 to the right of data1 //move n/2 elements from the right of data1 and move to data2
template <class T>
void split(T data1[], int& n1, T data2[], int& n2) {
    int count = n1 / 2;
    int start = n1 - count;

    for (int i = start; i < n1; ++i) {
        attach_item(data2, n2, data1[i]);
    }
    n1 = start;
}


template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){ //overwrite
    int dataCount;  
    for(dataCount = 0; dataCount < src_size; dataCount++){
        dest[dataCount] = src[dataCount]; 
    }
    dest_size = src_size; 
}             //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1) {
    for (int i = 0; i < n; ++i) {
        if (i == pos)
            cout << "[" << data[i] << "] ";
        else
            cout << data[i] << " ";
    }

    cout << endl;
}//print array data

template <class T>
bool is_gt(const T data[], int n, const T& item) {
    for (int i = 0; i < n; ++i) {
        if (!(item > data[i]))
            return false;
    }

    return true;
} //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item) {
    for (int i = 0; i < n; ++i) {
        if (!(item <= data[i]))
            return false;
    }

    return true;
}//item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator<<(ostream& outs, const vector<T>& list) {
    for (const T& item : list) {
        outs << item << " ";
    }

    return outs;
}// print vector list 

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    list.push_back(addme); 
    return list; //for now
}//list.push_back addme 

#endif
