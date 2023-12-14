#ifndef EVAL_H 
#define EVAL_H 

#include "../../includes/table/table.h"
class Evaluation{
    public: 
    Evaluation(); 
    Evaluation(Table& t); 
    private: 
    Table toBeEval; 
}; 

#endif