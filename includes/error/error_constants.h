#ifndef ERROR_CONSTANTS_H 
#define ERROR_CONSTANTS_H

//error codes 
const int INVALID_COMMAND_ERROR = 0; 

//make table errors
const int MISSING_KEYWORD_TABLE_ERROR = 1; 
const int MISSING_KEYWORD_FIELDS_ERROR = 3; 
const int MISSING_FIELD_NAMES_ERROR = 4; 

//insert errors
const int MISSING_KEYWORD_INTO_ERROR = 6; 
const int MISSING_KEYWORD_VALUES_ERROR = 8; 
const int MISSING_VALUES_ERROR = 9; 

//select errors 
const int MISSING_FIELDS_ERROR = 11; 
const int MISSING_KEYWORD_FROM_ERROR = 12; 
const int MISSING_KEYWORD_WHERE_ERROR = 201; 
const int MISSING_CONDITION_ERROR = 15; //no condition after where

//get fields errors
const int MISSING_KEYWORD_FIELDS_GET_ERROR = 18; 
const int MISSING_KEYWORD_FROM_GET_ERROR = 19; 
#endif