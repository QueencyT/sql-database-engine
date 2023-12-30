#ifndef OPERATOR_H 
#define OPERATOR_H 
#include <iostream>
#include "../../includes/token/token.h"
#include "../../includes/table/constants.h"

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


Operator::Operator() : Token(OPERATOR_TYPE){
    precedence = -1; 
}

Operator::Operator(int prec) : Token(OPERATOR_TYPE){
    precedence = prec; 
}

//parentheses precedence already set inside parentheses class 

Operator::Operator(int type, string val) : Token(type, val){
    if(type == RELATIONAL_TYPE){
        precedence = RELATIONAL_PRECEDENCE; 
    }
    else if(type == LOGICAL_TYPE){
        if(val == "and"){
            precedence = LOGICAL_AND_PRECEDENCE; 
        }
        else if(val == "or"){
            precedence = LOGICAL_OR_PRECEDENCE; 
        }
        //precedence = LOGICAL_PRECEDENCE; 
    }
    else{
        //cout<<"setting parentheses prec: \n"; 
        //cout<<"INVALID OPERATOR TYPE: OPERATOR NOT LOGICAL/RELATIONAL\n"; 
    }
}

Operator::Operator(int opType, string val, int prec) : Token(opType, val){
    if(opType == RELATIONAL_TYPE){
        precedence = RELATIONAL_PRECEDENCE; 
    }
    else if(opType == LOGICAL_TYPE){
        if(val == "and"){
            precedence = LOGICAL_AND_PRECEDENCE; 
        }
        else if(val == "or"){
            precedence = LOGICAL_OR_PRECEDENCE; 
        }
        //precedence = LOGICAL_PRECEDENCE; 
    }
    else{
        //cout<<"setting parentheses prec: \n"; 
        //cout<<"INVALID OPERATOR TYPE: OPERATOR NOT LOGICAL/RELATIONAL\n"; //if here we are parentheses 
        //precedence = prec; 
    }
}

int Operator::getPrecedence(){
    return precedence; 
}

void Operator::setPrecedence(int prec){
    precedence = prec; 
}

#endif