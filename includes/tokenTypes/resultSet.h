#ifndef RESULT_SET_H 
#define RESULT_SET_H
#include <vector>
#include "../../includes/token/token.h"

class Result_Set : public Token{
    public: 
    Result_Set(); 
    Result_Set(vector<long> recs); 
    vector<long> getSet(); 
    private: 
    vector<long> recnos; 
};

Result_Set::Result_Set() : Token(RESULT_SET_TYPE){

}

Result_Set::Result_Set(vector<long> recs) : Token(RESULT_SET_TYPE){
    recnos = recs; 
}

vector<long> Result_Set::getSet(){
    return recnos; 
}

#endif