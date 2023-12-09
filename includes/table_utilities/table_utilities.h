#ifndef TABLE_UTILITIES 
#define TABLE_UTILITIES 
#include <iostream>
#include "../../includes/tokenizer/constants.h"

using namespace std; 

void init_table(int _table[][MAX_COLUMNS]){ //working 
    for(int i = 0; i < MAX_ROWS; i++){
        for(int n = 0; n < MAX_COLUMNS; n++){
            _table[i][n] = -1; 
        }
    }
}

void print_table(int _table[][MAX_COLUMNS]){ //working
    for(int i = 0; i < MAX_ROWS; i++){
        for(int n = 0; n < MAX_COLUMNS; n++){
            cout<<"["<<_table[i][n]<<"] "; 
        }
        cout<<endl; 
    }
}

void mark_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 1; //marked with one for sucess 
}

void mark_not_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 0; //marked with zero for NOT success, not necessarily fail though
}

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state){
    return (_table[state][0] == 1); 
}
//Mark a range of cells in the array. 
//with a certain state? 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state){
    for(int column = from; column <= to; column++){ //<= ? --> might be one off --> must make sure 
        _table[row][column] = state; 
    }
}//make sure being updated properly 

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state){
    table[row][column] = state; 
}

#endif