#ifndef SCONSTANTS_H 
#define SCONSTANTS_H

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!+-%&|";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char PUNC[] = "?.,:;'`~!";
const int START_DOUBLE = 0;
const int START_SPACES = 4;
const int START_ALPHA = 6;
const int START_OPERATOR = 20;
const int START_PUNC = 10;

//token types:
const int TOKEN_NUMBER = 1;
const int TOKEN_ALPHA = 2;
const int TOKEN_SPACE = 3;
const int TOKEN_OPERATOR = 4;
const int TOKEN_PUNC = 5;

const int TOKEN_UNKNOWN = -1;
const int TOKEN_END = -2;

//index -> states --> values TokenTypes
const int SUCCESS_STATES[] = {-1, TOKEN_ALPHA, TOKEN_NUMBER,-1, -1, TOKEN_SPACE, TOKEN_PUNC}; 

//arrays denoting what type of state it is, 
const int COMMAND_STATES[] = {0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0}; //command states = 1,6 hence the 1 values
const int TABLE_NAME_STATES[] = {0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0};
const int WHERE_STATE[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}; 
const int VALUES_STATE[] = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}; 
const int FIELD_NAME_STATE[] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1};
const int CONDITION_STATE[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}; 
const int COL_STATE[] = {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}; 


//STRING STATES 
const int MAKE = 1; 
const int CREATE = 1; 
const int TABLE = 2; 
const int FIELDS = 4; 
const int INSERT = 6; 
const int INTO = 7; 
const int SELECT = 11; 
const int VALUES = 9; 
const int FROM = 13; 
const int WHERE = 14;
const int ALL = 12; 
const int SYMBOL = 15; 
#endif