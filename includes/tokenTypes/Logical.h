#ifndef LOGICAL_H 
#define LOGICAL_H 

#include "../../includes/token/token.h"
#include "../../includes/tokenTypes/Operator.h"
#include "../../includes/table/constants.h"

using namespace std; 

class Logical : public Operator{
    public: 
        Logical(string logicalOp); 
    private: 
}; 


Logical::Logical(string logicalOp) : Operator(LOGICAL_TYPE, logicalOp){ //MODIFIED, was LOGICAL_PRECEDENCE being passed in befroe 
    if(getToken() == "and"){
       // cout<<"setting and precedence\n"; 
        setPrecedence(LOGICAL_AND_PRECEDENCE);  
    }
    if(getToken() == "or"){
        //cout<<"setting or precedence\n"; 
        setPrecedence(LOGICAL_OR_PRECEDENCE); 
    }    
}

#endif 