#ifndef PARSER_H
#define PARSER_H 
#include <vector>
#include "../../includes/tokenizer/stokenize.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/table/typedefs.h"

class Parser{
    public: 
        Parser(); 
        Parser(char s[]); 
        void set_string(string s); 
        void getTokens(); //public for now
        MMap<string,string> parse_tree(); 
    private: 
        string expression; 
        vector<string> tokens; 
        Map<string, int> keywordMap; 
        int stateMachine[MAX_ROWS][MAX_COLUMNS];  
        MMap<string,string> ptree; 

        void printTokens(vector<string> toks); //helper function just to print tokens
        void makeTable();
        void initKeywords(); 

        //boolean helper functions --> tells us information about what state we are in 
        bool isCommandState(int state){ return COMMAND_STATES[state];}
        bool isTableNameState(int state){return TABLE_NAME_STATES[state];}
        bool isWhereState(int state){return WHERE_STATE[state];}
        bool isValueState(int state){return VALUES_STATE[state];}
        bool isConditionState(int state){return CONDITION_STATE[state];}
        bool isFieldNameState(int state){return FIELD_NAME_STATE[state];}
        bool isKeyword(string token){return keywordMap.contains(token);}
        bool isColState(int state){return COL_STATE[state];}
        //helper function tell us which state to go to next
        int getNextState(string tok); 
}; 



Parser::Parser(char s[]){
    makeTable(); 
    initKeywords(); 
    string exp(s); 
    expression = exp; 
    getTokens(); 
}

Parser::Parser(){
    makeTable();
    initKeywords();
    expression = ""; 
    getTokens();  
}

void Parser::initKeywords(){
    keywordMap.insert("make", 1);
    keywordMap.insert("create",1);
    keywordMap.insert("table",2); 
    keywordMap.insert("fields",4); 
    keywordMap.insert("insert",6); 
    keywordMap.insert("into",7); 
    keywordMap.insert("select",11); 
    keywordMap.insert("*", 12); 
    keywordMap.insert("from", 13); 
    keywordMap.insert("where", 14); 
    keywordMap.insert("values", 9); 
}

void Parser::makeTable(){
    init_table(stateMachine); 
    //state 0 - start state 
    //state 1 - MAKE state - command state
    //state 2 - TABLE state - command state 

    //select stateMachine path 
    mark_cell(0,stateMachine,SELECT, 11);  
    mark_cell(11,stateMachine,ALL, 12); 
    mark_cell(11,stateMachine,SYMBOL, 17); //aka if we get a field name
    mark_cell(17,stateMachine,SYMBOL,17); 
    mark_cell(17,stateMachine,FROM, 13); 
    mark_cell(15,stateMachine,SYMBOL, 16); 
    mark_cell(16,stateMachine,SYMBOL,16); 
    mark_cell(12,stateMachine,FROM,13); 
    mark_cell(13,stateMachine,SYMBOL,14);
    mark_cell(14,stateMachine,WHERE,15); 

    //make table stateMachine path
    mark_cell(0, stateMachine, CREATE, 1); 
    mark_cell(0,stateMachine,MAKE,1); 
    mark_cell(1,stateMachine,TABLE,2); 
    mark_cell(2,stateMachine,SYMBOL,3); 
    mark_cell(3,stateMachine,FIELDS, 4);
    mark_cell(4,stateMachine,SYMBOL,5); 
    mark_cell(5,stateMachine,SYMBOL,5);  

    //insert into stateMachine path 
    mark_cell(0,stateMachine,INSERT, 6); 
    mark_cell(6,stateMachine,INTO,7);
    mark_cell(7,stateMachine,SYMBOL,8); 
    mark_cell(8,stateMachine,VALUES, 9);  
    mark_cell(9,stateMachine,SYMBOL,10); 
    mark_cell(10,stateMachine,SYMBOL,10); 
}


void Parser::set_string(string s){
    expression = s; 
    getTokens();
}

void Parser::getTokens(){//gets the tokens without punc, and pushes it into tokens
    char exp[expression.length() + 1]; 
    strcpy(exp, expression.c_str()); 
    STokenizer tokenizer(exp);  
    string tokVal; 
    tokenizer >> tokVal;
    while(tokenizer.more()){  
        if(!tokVal.empty()){
            tokens.push_back(tokVal);  
        }
          
        tokenizer >> tokVal; 
    }
}

MMap<string,string> Parser::parse_tree(){
    int currState = 0, nextState = 0, i; 
    string val;
    MMap<string,string> returnThis; 

    if(isKeyword(tokens[0]))
        currState = keywordMap.get(tokens[0]);

    for(i = 0; i < tokens.size() && currState != -1; i++){
        if(i < tokens.size() - 1)
              nextState = getNextState(tokens[i+1]);  

        if(isCommandState(currState)){//have an array with all the command states //if curr state is a command state
            ptree.insert("command", tokens[i]); 
        }
        else if(isTableNameState(currState)){//one of the table name states  
            ptree.insert("table_name", tokens[i]); 
        }
        else if(isColState(currState)){
            ptree.insert("col", tokens[i]); 
        }
        else if(isWhereState(currState)){
            ptree.insert("where", "yes"); 
        }
        else if(isConditionState(currState)){
            ptree.insert("condition", tokens[i]); 
        }
        else if(isFieldNameState(currState)){
            ptree.insert("fields", tokens[i]);
        }
        else if(isValueState(currState)){
            ptree.insert("values", tokens[i]); 
        }
        currState = stateMachine[currState][nextState]; //from currState we got this newState where will we go
    }
    
    //cout<<"end state: "<<currState<<endl; 
   if(currState == -1){
       cout<<"FAILED: INCORRECT SYNTAX FOUND: "<< tokens[i]<<endl; 
       //ptree.clear(); 
    }
    returnThis = ptree;
    tokens.clear();
    ptree.clear();
    return returnThis; 
}//if we fail, reset ptree, reset everything, 

void Parser::printTokens(vector<string> toks){
    for(int i = 0; i < toks.size(); i++){
      cout<<"token "<<i<<": |"<<toks[i]<<"|"<<endl; 
    }
}

int Parser::getNextState(string token){
    if(isKeyword(token)){
        return keywordMap.get(token); 
    }
    else{//is a symbol so return val for symbol
        return SYMBOL; 
    }
}
#endif 