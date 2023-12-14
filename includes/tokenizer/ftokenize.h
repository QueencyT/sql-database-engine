#ifndef FTOKENIZE_H 
#define FTOKENIZE_H 

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cassert>
#include "../../includes/tokenizer/constants.h"
#include "../../includes/tokenizer/token.h" 
#include "../../includes/tokenizer/stokenize.h" 

using namespace std; 

class FTokenizer
{
public:
    const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer(char* fname);
    SToken next_token(); 
    bool more();        //returns the current value of _more
    int pos();          //returns the value of _pos
    int block_pos();     //returns the value of _blockPos
    friend FTokenizer& operator >> (FTokenizer& f, SToken& t);
private:
    bool get_new_block(); //gets the new block from the file
    ifstream _f;   //file being tokenized
    STokenizer _stk;     //The STokenizer object to tokenize current block
    int _pos;           //Current position in the file
    int _blockPos;      //Current position in the current block
    bool _more;         //false if last token of the last block
                        //  has been processed and now we are at
                        //  the end of the last block.
    bool _done; 
};

FTokenizer::FTokenizer(char* fname){
    //make an ifstream obj 
    _f.open(fname); 
    assert(_f.is_open()); 
    get_new_block(); 
}

SToken FTokenizer::next_token(){
    SToken tok; 
    _stk >> tok; 
    _pos++;
    //cout<<"length: "<<tok.token_str().length()<<endl; 
    _blockPos += tok.token_str().length();
    return tok; 
}

int FTokenizer::pos(){
    return _pos; 
}         //returns the value of _pos


int FTokenizer::block_pos(){
    return _blockPos; 
}     //returns the value of _blockPos

FTokenizer& operator >> (FTokenizer& f, SToken& t){
    if(!f._f.eof() && f._stk.done()){
        f.get_new_block();
    }
    t = f.next_token(); 
    string tokStr = t.token_str(); 
    return f; 
}

bool FTokenizer::more(){
    return (!_f.eof() || !_stk.done()); //end of file? 
}

bool FTokenizer::get_new_block(){
    char tempStr[MAX_BLOCK + 1];  //want to be one more than max so we can fit in '\0'
    _f.read(tempStr, MAX_BLOCK); 
    int size = _f.gcount(); 
    tempStr[size] = '\0'; 
    _blockPos = 0; 
    _stk = STokenizer(tempStr); 
    cout<<tempStr<<endl; 
    return (tempStr[0] != '\0'); 
} //gets the new block from the file
//boolean for if it was able to get new block?

#endif