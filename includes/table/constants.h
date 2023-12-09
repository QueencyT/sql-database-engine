#ifndef TABLE_CONSTANTS_H 
#define TABLE_CONSTANTS_H 

const int OPERATOR_TYPE = 1; 
const int RELATIONAL_TYPE = 2; 
const int LOGICAL_TYPE = 3; 
const int PAREN_TYPE = 4; 
const int TOKEN_STR_TYPE = 5; 

const int RELATIONAL_PRECEDENCE = 20; 
//const int LOGICAL_PRECEDENCE = 10; 
const int LOGICAL_AND_PRECEDENCE = 15; 
const int LOGICAL_OR_PRECEDENCE = 10; 
const int LEFT_PAREN_PRECEDENCE = 0; 
const int RIGHT_PAREN_PRECEDENCE = 30; 



#endif 