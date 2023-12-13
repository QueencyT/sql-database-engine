#ifndef TOKEN_H
#define TOKEN_H 
#include <string>
#include "../../includes/table/constants.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/queue/MyQueue.h"

using namespace std; 

class Token{
    public: 
        Token(); 
        Token(int typeVal);
        Token(int typeVal, string tokVal); 
        int getType(); 
        string getToken();
        Queue<Token*> createTokens(vector<string> tokVals);  
        friend ostream& operator <<(ostream& outs, const Token& printMe){
            outs<<printMe.tok; 
            return outs; 
        }
        
    private: 
        int type; 
        string tok; 
        Map<string,int> relationalTypes; //a map of relational operators, a map of logical operators, a map of 
        Map<string,int> logicalTypes; 
        void init_token_types(); 
        Token* createToken(string tokVal); 
        
}; 


#include "../../includes/tokenTypes/Operator.h"
#include "../../includes/tokenTypes/Logical.h"
#include "../../includes/tokenTypes/Relational.h"
#include "../../includes/tokenTypes/TokenStr.h"
#include "../../includes/tokenTypes/Paren.h"

//operator, not operator, paren


void Token::init_token_types(){
    relationalTypes.insert(">=", RELATIONAL_TYPE); 
    relationalTypes.insert("<=", RELATIONAL_TYPE); 
    relationalTypes.insert("=", RELATIONAL_TYPE); 
    relationalTypes.insert("<", RELATIONAL_TYPE); 
    relationalTypes.insert(">", RELATIONAL_TYPE); 
    logicalTypes.insert("and", LOGICAL_TYPE); 
    logicalTypes.insert("or", LOGICAL_TYPE); 

}

Token* Token::createToken(string tokVal){
    if(relationalTypes.contains(tokVal)){
       return (new Relational(tokVal)); 

    }
    else if(logicalTypes.contains(tokVal)){
        return (new Logical(tokVal)); 
    }
    else if(tokVal == "(" || tokVal == ")"){
        return (new Paren(tokVal));
    }
    else{
        return (new TokenStr(tokVal)); 
    }
}

Queue<Token*> Token::createTokens(vector<string> tokVals){
    Queue<Token*> result; 
    for(int i = 0; i < tokVals.size(); i++){
        result.push(createToken(tokVals[i])); 
    }
    return result; 
}


Token::Token(){
    init_token_types();
    type = -1; 
    tok = ""; 
}

Token::Token(int typeVal){
    init_token_types();
    type = typeVal; 
    tok = ""; 
}

Token::Token(int typeVal, string tokVal){
    init_token_types();
    type = typeVal; 
    tok = tokVal; 
}

int Token::getType(){
    return type; 
}

string Token::getToken(){
    return tok; 
}

#endif