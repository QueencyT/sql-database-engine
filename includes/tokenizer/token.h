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

#endif