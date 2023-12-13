#ifndef PAREN_H 
#define PAREN_H 

#include "../../includes/token/token.h"
#include "../../includes/tokenTypes/Operator.h"
#include "../../includes/table/constants.h"

using namespace std; 

class Paren : public Operator{
    public: 
        Paren(); 
        Paren(string par); 
    private: 
}; 


Paren::Paren() : Operator(PAREN_TYPE){

}

Paren::Paren(string par) : Operator(PAREN_TYPE, par){
    if(par == "("){
        setPrecedence(LEFT_PAREN_PRECEDENCE);
    }
    else if(par == ")"){
        setPrecedence(RIGHT_PAREN_PRECEDENCE);
    }
    else{
        cout<<"INVALID: NOT A PARENTHESES\n";
    } 
}
//right paren, left paren

#endif 