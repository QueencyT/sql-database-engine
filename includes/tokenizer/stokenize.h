#ifndef STOKENIZER_H 
#define STOKENIZER_H 

#include <iostream>
#include <string.h>
#include "../../includes/tokenizer/constants.h"
#include "../../includes/tokenizer/token.h"
#include "../../includes/table_utilities/table_utilities.h"

using namespace std; 

class STokenizer
{
public:
    STokenizer(); 
    STokenizer(char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, SToken& t);

    //set a new string as the input string
    void set_string(char str[]);

    
    //extract the longest string that match one of the acceptable token types
    bool get_token(int start_state, string& token); //true of false means ? sucesffuly got token?
    //MAKE GET TOKEN PRIVATE AGAIN LATER

    
    //This can realistically be used on a small table
    void print_table(int _table[][MAX_COLUMNS]);

    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    /*static*/ 
    bool _done; 
    int endState; 

    int _table[MAX_ROWS][MAX_COLUMNS];

private:
    //create table for all the tokens we will recognize (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);
    void show_string(char s[], int _pos);
    void setDone(bool val); 

    
};


STokenizer::STokenizer(){
    _buffer[MAX_BUFFER] = {' '}; //maybe??
    make_table(_table); 
    _pos = 0; 
    endState = 0; 
    _done = false; 
}
STokenizer::STokenizer(char str[]){
    strcpy(_buffer, str); 
    make_table(_table);
    _pos = 0; 
    endState = 0; 
    _done = false; 
}

void STokenizer::setDone(bool val){
    _done = val;
}

//TABLE STUFF 
//COLUMN 0 (first column) - is the state (row number) a sucess state or not 
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //must verify if everything init to correct states - have verified
    init_table(_table); 

    //state 1 - alpha state 
    //state 2 - decimal number state 
    //state 3 - decimal pt state 
    //state 4 - single number state 
    //state 5 - space state 
    //state 6 - punc state 
    //state 8 - quotation state 
    //state 9 - "Teresa Mae" - state (tokenize "Teresa Mae" as Teresa Mae)
    //state 15 - comparison operator state
    //state 25 - parentheses state 

    mark_not_success(_table,0); 
    mark_success(_table,1); 
    mark_success(_table,2); 
    mark_not_success(_table,3); 
    mark_success(_table,4); 
    mark_not_success(_table,5);  // mark_success(_table,5); originally
    mark_not_success(_table,6); //mark_success(_table,6);
    mark_success(_table, 25); 

    //added
    mark_success(_table,7); 
    mark_success(_table,8); 
    mark_success(_table, 9); 
    mark_success(_table, 15); 

    //for ALPHA 
    mark_cells(0, _table,'A','Z',1); 
    mark_cells(1,_table,'A','Z',1); 
    mark_cells(0,_table,'a','z',1); 
    mark_cells(1,_table,'a','z',1);
    //added -- for "Teresa Mae" state 
    mark_cells(8,_table, 'A', 'Z', 9); 
    mark_cells(8,_table, 'a','z', 9);
    mark_cells(9,_table,'A','Z', 9); 
    mark_cells(9,_table, 'a', 'z', 9); //state 9 being the "Teresa Mae" case where we want that to be one last name 


    //for Decimal Number 
    mark_cells(0, _table,'0','9', 2); 
    mark_cells(2,_table,'0', '9', 2); 
    mark_cells(3,_table, '0', '9', 4);

    //for single number 
    mark_cells(4,_table,'0','9', 4);
    
    //for spaces - only for state 9 "teresa mae" state  
   mark_cell(9, _table, ' ', 9);
   
    //for decimal pt 
    mark_cell(2,_table,'.',3); 

    //for punctuation - commas for now here - might need to change later 
    mark_cell(0, _table,'*', 7); 
    mark_cell(0, _table, 34, 8); //34 being quotation marks 
    mark_cell(9, _table, 34, 8);
    

    //for comparison operators 
    mark_cell(0,_table, '<', 15); 
    mark_cell(0,_table, '>', 15); 
    mark_cell(0,_table,'=', 15); 
    mark_cell(15,_table, '<', 15); 
    mark_cell(15,_table, '>', 15); 
    mark_cell(15,_table,'=', 15); 

    //for parentheses state
    mark_cell(0,_table,'(', 25); 
    mark_cell(0,_table,')',25); 
    //mark_cell(25,_table,'(', 25); 
    //mark_cell(25,_table,')',25); 


}

bool STokenizer::done(){
    return _done; 
    //return(_buffer[_pos] == '\0');
    //either > or >=, if having problems modify here
}

bool STokenizer::more(){
    return (!done()); //- 1 b/c not more if at end
}

void STokenizer::set_string(char str[]){
    strcpy(_buffer, str); 
}

bool STokenizer::get_token(int start_state, string& token){ 
    int state = start_state, lastSuccessPos = _pos; 
    string process = ""; 
    while((_buffer[_pos] > 0) && state != -1){ 
        state = _table[state][_buffer[_pos]];
        process += _buffer[_pos]; 
        if(is_success(_table, state)){  
            if(process[0] != 34) //ignoring quotation marks
                token += process;
            process = ""; 
            lastSuccessPos = _pos; 
        }
        _pos++; 
    }
    _pos = lastSuccessPos + 1; 
    endState = _table[0][_buffer[lastSuccessPos]]; 
    return (!token.empty()); 
} //true of false means ? successfully got a token?


STokenizer& operator >> (STokenizer& s, string& t){
    string tokStr; 
    if(s._buffer[s._pos] == '\0'){
        s._done = true; 
    }

    if(s.get_token(0, tokStr)){//if we successfully got a token
        t = tokStr; 
    }
    else{
        //cout<<"error\n";
        string error(1, s._buffer[s._pos - 1]); 
        t = ""; 
    }

    return s; 
}

//pos --> after 
STokenizer& operator >> (STokenizer& s, SToken& t){
    string tokStr; 
    if(s._buffer[s._pos] == '\0'){
        s._done = true; 
    }

    if(s.get_token(0, tokStr)){
        SToken newToken(tokStr,SUCCESS_STATES[s.endState]); 
        t = newToken; 
    }
    else{
        string error(1, s._buffer[s._pos - 1]); 
        SToken unknown(error, -1); 
        t = unknown;
    }
    return s; 
}

#endif