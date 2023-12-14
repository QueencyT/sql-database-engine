#ifndef SHUNTING_YARD 
#define SHUNTING_YARD 

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/table/constants.h"
#include "../../includes/tokenTypes/Operator.h"

class ShuntingYard{
    public: 
        ShuntingYard(); 
        ShuntingYard(Queue<Token*> infix); 
        Queue<Token*> postfix();
        Queue<Token*> postfix(Queue<Token*> infix); 
    private: 
        Queue<Token*> infix; 
        void operatorDecider(Token* popped, Queue<Token*>& symbols, Stack<Token*>& operators); 
        void popRest(Queue<Token*>& symbols, Stack<Token*>& operators); 
        void parenDecider(Token* popped, Queue<Token*>& symbols, Stack<Token*>& operators); 
}; 

ShuntingYard::ShuntingYard(){

}

ShuntingYard::ShuntingYard(Queue<Token*> infixQ){
    infix = infixQ; 
}

Queue<Token*> ShuntingYard::postfix(){
    return postfix(infix); 
}

void printQueue(const Queue<Token*>& someQueue){
    Queue<Token*>::Iterator iter = someQueue.begin(); 
    while(iter != nullptr){
        Token* tokenPtr = *iter; 
        cout<<"["<<tokenPtr->getToken()<<"] "; 
        iter++; 
    }
    cout<<endl; 
}

void printStack(const Stack<Token*>& someStack){
    Stack<Token*>::Iterator iter = someStack.begin(); 
    while(iter != nullptr){
        Token* tokenPtr = *iter; 
        cout<<"["<<tokenPtr->getToken()<<"] "; 
        iter++; 
    }
    cout<<endl; 
}

void ShuntingYard::parenDecider(Token* popped, Queue<Token*>& symbols, Stack<Token*>& operators){
    string tokVal = popped->getToken(); 
    if(tokVal == ")"){ 
        Token* op = popped; 
        while(!operators.empty() && op->getToken() != "("){
            op = operators.pop(); 
            if(op->getToken() != "(")
                symbols.push(op);  
        }
    }
    else{
        operators.push(popped);
    }
}


void ShuntingYard::popRest(Queue<Token*>& output, Stack<Token*>& operators){
    while(!operators.empty()){
        Token* op = operators.pop();
        if(!(op->getToken() == ")" || op->getToken() == "(")){
            output.push(op); 
        }
    }
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> inFix){
    Queue<Token*> numbers;
    Stack<Token*> operators;  
    while(!inFix.empty()){
        Token* popped = inFix.pop(); 
        if(popped->getToken() == ")" || popped->getToken() == "("){
            parenDecider(popped, numbers,operators); 
        }
        else if(popped->getType() == RELATIONAL_TYPE || popped->getType() == LOGICAL_TYPE){ 
            operatorDecider(popped, numbers, operators);  
        }
        else{
            numbers.push(popped); 
        }

    }
    //cout<<"here\n"; 
    popRest(numbers, operators);  
    return numbers; 
}

void ShuntingYard::operatorDecider(Token* popped, Queue<Token*>& symbols, Stack<Token*>& operators){
     Token* stackOp; 
     int precedence = static_cast<Operator*>(popped)->getPrecedence();

     //while operators stack not empty and the precedence of the popped operator is lower than the precednece of the operator on the stack 
    while(!operators.empty() && precedence <= static_cast<Operator*>((operators.top()))->getPrecedence()){//was <= 
        stackOp = operators.pop(); 
        symbols.push(stackOp); //add to output 
    }
    operators.push(popped); //push the popped op onto stack now in correct place 
}
#endif 