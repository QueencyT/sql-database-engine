#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H
#include "../../includes/bplustree/map.h"

vector<long> combine(vector<long> left, vector<long> right){
    Map<long, bool> leftVec;
    bool found;  

    for(int i = 0; i < left.size(); i++){
        leftVec.insert(left[i], true); 
    }

    for(int i = 0; i < right.size();i++){ //in order or not hmm?
        found = leftVec.get(right[i]); 
        if(!found)//left doesn't already have this value
            left.push_back(right[i]);
    }
    return left; 
}

vector<long> intersection(vector<long> left, vector<long> right){//get what's in common with the two vecs
    Map<long, bool> leftVec; 
    vector<long> newVec; 
    bool found; 

    for(int i = 0; i < left.size(); i++){
        leftVec.insert(left[i], true); 
    }

    for(int i = 0; i < right.size(); i++){
        found = leftVec.get(right[i]); 
        if(found)
            newVec.push_back(right[i]); 
    }
    return newVec; 
}

#endif