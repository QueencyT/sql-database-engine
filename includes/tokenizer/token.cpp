#include "../../includes/tokenizer/token.h"


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