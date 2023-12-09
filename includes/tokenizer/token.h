#ifndef STOKEN_H 
#define STOKEN_H 
#include <iostream>
#include "../../includes/tokenizer/constants.h"

using namespace std; 
class SToken
{
public:
    //CTORS
    SToken() : _token(""), _type(TOKEN_UNKNOWN){}; 
    SToken(string str, int type) : _token(str), _type(type){};  

    friend ostream& operator <<(ostream& outs, const SToken& t);
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type; //0 --> char, 1 --> num, 2--> punc, 3 --> space
};


ostream& operator <<(ostream& outs, const SToken& t){
    outs<<t._token; 
    return outs; 
}

int SToken::type() const{
    return _type; 
}

string SToken::type_string() const{ //must ask
    switch(_type){
        case TOKEN_NUMBER:
            return "NUMBER"; 
        case TOKEN_ALPHA: 
            return "ALPHA";
        case TOKEN_SPACE:
            return "SPACE"; 
        case TOKEN_PUNC:
            return "PUNC"; 
        case TOKEN_OPERATOR: 
            return "OPERATOR"; 
    }
    return "UNKNOWN TYPE"; 
}

string SToken::token_str() const{
    return _token; 
}

#endif