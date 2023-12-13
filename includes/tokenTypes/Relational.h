#ifndef RELATIONAL_H 
#define RELATIONAL_H 

#include "../../includes/tokenTypes/Operator.h"
#include "../../includes/table/constants.h"

//=, >, <, <=, >=

class Relational : public Operator{
    public: 
        Relational(string relationalOp); //will call ctor of Token, and set type that way
    private: 
    //type = 1
}; 

Relational::Relational(string relationalOp) : Operator(RELATIONAL_TYPE, relationalOp, RELATIONAL_PRECEDENCE){

}

#endif 