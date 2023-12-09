#ifndef BTREE_ARRAY_FUNCTIONS_H 
#define BTREE_ARRAY_FUNCTIONS_H

#include <vector>
#include <iostream>

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
int index_of_maximal(T data[ ], int n){ //assuming n is size? 
int max = data[0];
    for(int i = 0; i < n; i++){
        if(max < data[i]){//can probably replace with maximal function instead 
            max = data[i]; 
        }
    }
    return max; 
}


template <class T>
void insert_item(T data[ ], int insertIndex, int& n, T entry){ //assuming at least one space //MUST TEST
//n should be one past actual index 
    for(int i = n; i > insertIndex; i--){
       T temp = data[i]; 
       data[i] = data[i-1]; 
       data[i - 1] = temp; 
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
    entry = data[n]; 
    n--;
}//remove the last element in data and place
//it in entry

template <class T>
void delete_item(T data[ ], int deleteIndex, int& n, T& entry){ //ok seems to be working so far
    entry = data[deleteIndex]; 
   for(int i = deleteIndex; i < n - 1; i++){
        T temp = data[i]; 
        data[i] = data[i + 1]; 
        data[i + 1] = temp; 
   }
   n--; 
}//delete item at index i and place it in entry

//delete from data2 and then merge //must test //will keep eye
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
int itemsToDelete = n2; 
T deleted; 
    for(int i = 0; i < itemsToDelete; i++){
        delete_item(data2, 0, n2, deleted);  
        insert_item(data1, n1,n1, deleted); 
    }
} 

//append data2 to the right of data1

//0 1 2 3
template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){//two separate BTree and their data arrs 
int numToDelete = n1/2; 
T deleted; 
int del;
    for(int i = 0; i < numToDelete; i++){
        delete_item(data1, n1 - 1, n1, deleted); //as long as my delete item is working correctly shouldnt cause problems
        int temp = n1;
        insert_item(data2, 0, n2, deleted);
        n1 = temp;
    }
}
//move n/2 elements from the right of data1 and move to data2

template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size){ //overwrite
    int dataCount;  
    for(dataCount = 0; dataCount < src_size; dataCount++){
        dest[dataCount] = src[dataCount]; 
    }
    dest_size = src_size; 
}             //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1){

}  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item){
    return true; //for now
}     //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item){
    return true; //for now //might use later 
} //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    return outs; 
}//print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){//cause what is this for?? 
    list.push_back(addme); 
    return list; //for now
}//list.push_back addme 

#endif 
