#ifndef TOKENSTR_H 
#define TOKENSTR_H 

#include "../../includes/table/constants.h"
#include "../../includes/token/token.h"

using namespace std; 

class TokenStr : public Token{
    public: 
        TokenStr(string tok); 
    private: 
}; 

TokenStr::TokenStr(string tok) : Token(TOKEN_STR_TYPE, tok){

}
#endif