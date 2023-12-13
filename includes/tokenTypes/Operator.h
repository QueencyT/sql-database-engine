#ifndef OPERATOR_H 
#define OPERATOR_H 
#include <iostream>

#include "../../includes/table/constants.h"
#include "../../includes/token/token.h"


using namespace std; 

class Operator : public Token{ //and relational and logical will inerit from here
    public: 
        Operator(); 
        Operator(int prec); 
        Operator(int type, string val); 
        Operator(int type, string val, int prec); 
        int getPrecedence(); 
        void setPrecedence(int prec); 
    private: 
        int precedence; 
}; 

#include "../../includes/tokenTypes/Operator.h"

Operator::Operator() : Token(OPERATOR_TYPE){
    precedence = -1; 
}

Operator::Operator(int prec) : Token(OPERATOR_TYPE){
    precedence = prec; 
}

Operator::Operator(int type, string val) : Token(type, val){

}

Operator::Operator(int opType, string val, int prec) : Token(opType, val){

}

int Operator::getPrecedence(){
    return precedence; 
}

void Operator::setPrecedence(int prec){
    precedence = prec; 
}

#endif 