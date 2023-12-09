#ifndef TABLE_H 
#define TABLE_H 
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "../../includes/binary_files/utilities.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/binary_files/file_record.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/table/typedefs.h"


#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/token.h"
#include "../../includes/tokenTypes/Logical.h"
#include "../../includes/tokenTypes/Relational.h"
#include "../../includes/tokenTypes/TokenStr.h"
#include "../../includes/table/constants.h"

#include "../../includes/shunting_yard/shunting_yard.h"


using namespace std; 


class Table{
    public:
        Table();
        Table(const char fileName[]); 
        Table(const char fileName[], vector<string> fieldNames); 

        void insert_into(vector<string> data);

        Table select(vector<string> fields, Queue<Token*> postFix); //post fix table 
        Table select(vector<string> fields, string field, string op, string key); 
        Table select(vector<string> fields, vector<string> infixCondition); 
        Table select_all(); 
        Table select_all(vector<string> fields); //return table?
        string getTableName(); 
        vector<string> getFields(); 

        vector<long> select_recnos(); 
        Table vector_to_table(vector<string> fields, vector<long> recnos);
        void print_table() const;
        void printVec(vector<long> recnos);

        friend ostream& operator <<(ostream& outs, const Table& printThis){//make const later
            printThis.print_table();
            return outs; 
        }

        friend ostream& operator<<(ostream& outs, const vector<long>& recs){
            for(int i = 0; i < recs.size();i++){
                outs<<recs[i]<< " "; 
            }
            outs<<endl; 
            return outs; 
        }

        //logical eval functions  //public for now
        vector<long> combine(vector<long> left, vector<long> right);
        vector<long> intersection(vector<long> left, vector<long> right);
       
    private: 
        vector<MMap<string,long>> mTable; //each index represents a 
        Map<string, long> ourFields; 
        vector<long> selectedVec; //for select recnos (all the vecs in a table)
        vector<string> fields; 
        static int serial;
        string filName, saveName; 
    
        //private helper funcs 
        //construction functions 
        void initTable(fstream& readThis); 
        void buildIndexes(vector<string> fields);

        //evaluation funcs
        vector<long> eval(vector<long> left, string op, vector<long> right); //for relational
        vector<long> eval(string field, string op, string key);//for logical

        vector<long> iterate(MMap<string, long>::Iterator start, MMap<string, long>::Iterator end);

        

        vector<string> printFields(vector<string> f){
        for(int i = 0; i < f.size(); i++){
            cout<<f[0]<<" "; 
        }
        cout<<endl; 
    }
}; 
//a vector of multimaps 

vector<string> Table::getFields(){
    return fields; 
}
string Table::getTableName(){
    return filName; 
}

int Table::serial = 0; 

void Table::initTable(fstream& readThis){//init table from fiel 
    FileRecord recordReader; 
    int i= 0;
    int bytes = recordReader.read(readThis, i);
    while (bytes>0){
        vector<string> rec = recordReader.get_record(); 
        for(int n = 0; n < rec.size(); n++){
            mTable[n].insert(rec[n], i); 
        }
        bytes = recordReader.read(readThis, ++i);
    }
}

void Table::buildIndexes(vector<string> fields){
     for(int i = 0; i < fields.size();i++){
        MMap<string, long> aMap; 
        mTable.push_back(aMap); 
        ourFields.insert(fields.at(i), i);
    }
}

Table::Table(){
    fstream aFile; 
    open_fileW(aFile, "temp.bin"); //opening file //still havent done anything with field names
    serial++; 
}

Table::Table(const char fileName[]){ 
    fstream aFile, savedInfo; 
    FileRecord recordReader; 
    filName = fileName; 
    saveName = filName + "info.txt"; 


    open_fileRW(aFile, fileName); //opening file 
    open_fileRW(savedInfo, saveName.c_str()); 
    recordReader.read(savedInfo, 0); //reading the saved info 
    vector<string> savedFields = recordReader.get_record(); 
    buildIndexes(savedFields);
   // cout<<"ctor fired\n"; 
    fields = savedFields; 
    initTable(aFile); 

    serial++;  
    aFile.close();
}

Table::Table(const char fileName[], vector<string> fieldNames){
    FileRecord saveInfo = FileRecord(fieldNames); 
    fstream aFile, info;  
    filName = fileName;
    saveName = filName + "info.txt"; 

    open_fileW(aFile, filName.c_str()); 
    open_fileW(info, saveName.c_str()); 
    saveInfo.write(info);

    buildIndexes(fieldNames); 
    fields = fieldNames; 

    serial++; 
    aFile.close();
}

void Table::insert_into(vector<string> data){//insert the rparts of the record into the correct multimaps
    FileRecord recordedFiles = FileRecord(data); //write fiiles 
    fstream aFile; 
    open_fileRW(aFile, filName.c_str()); 
    aFile.seekg(0,aFile.end); 
    int recordNum = recordedFiles.write(aFile);

    for(int i = 0; i < data.size(); i++){
        mTable[i].insert(data[i], recordNum); 
    }
    aFile.close();
}

//vector<string> condition = {"(", "age", "<", "17", "or", "age", ">", "20", ")", "and", "lname", "=", "Jackson"};
//OPERATORS 
    //=, or, <, >, and, <=, >=
//display only lname and age 

void Table::printVec(vector<long> recnos){
    for(int i = 0; i < recnos.size(); i++){
        cout<<"["<<recnos.at(i)<<"] "; 
    }
    cout<<endl; 
}

vector<long> Table::iterate(MMap<string, long>::Iterator start, MMap<string, long>::Iterator end){
    MPair<string, long> foundRecs; 
    for(MMap<string,long>::Iterator begin = start; begin != end; begin++){
        foundRecs = foundRecs + *begin; 
    }
    return foundRecs.value_list; 
}

vector<long> Table::eval(string field, string op, string key){
    int index = ourFields.get(field);
    vector<long> recnos; 
    MMap<string, long>::Iterator beg = mTable[index].begin(), end = mTable[index].end(), upBound = mTable[index].upper_bound(key),
    lowBound = mTable[index].lower_bound(key);

    if(op == "="){ //maybe abstract out into operator class --> and the function will 
        recnos = mTable[index].get(key); 
    }else if(op == ">"){
        recnos = iterate(upBound, end); 
    }else if(op == "<"){
        recnos = iterate(beg, lowBound); //lowerbound will get == or > // but will stop before then
    }else if(op == ">="){
        recnos = iterate(lowBound, end); 
    }else if(op == "<="){
       // cout<<"op: "<<op<<endl; 
        MPair<string, long> low; 
        if(lowBound != mTable[index].end())
            low = *lowBound; 
       //cout<<"key: "<<key<<endl; 
      // cout<<"low key: "<<low.key<<endl; 
       if(lowBound != mTable[index].end() && low.key == key){
        MMap<string,long>::Iterator next = lowBound++;
        recnos = iterate(beg, next); 
       }
       else{//before there was no else just if //// recnos = knd
        recnos = iterate(beg, lowBound); 
       }
    }else{
        cout<<"INVALID OPERAND TYPE\n"; 
    }
    selectedVec = recnos; 
    return recnos; 
}


vector<long> Table::combine(vector<long> left, vector<long> right){
    Map<long, bool> leftVec;
    bool found;  

    for(int i = 0; i < left.size(); i++){
        leftVec.insert(left[i], true); 
    }

    for(int i = 0; i < right.size();i++){ //in order or not hmm?
        found = leftVec.get(right[i]); 
        if(!found)//left doesn't already have this value
            left.push_back(right[i]);
    }
    return left; 
}

vector<long> Table::intersection(vector<long> left, vector<long> right){//get what's in common with the two vecs
    Map<long, bool> leftVec; 
    vector<long> newVec; 
    bool found; 

    for(int i = 0; i < left.size(); i++){
        leftVec.insert(left[i], true); 
    }

    for(int i = 0; i < right.size(); i++){
        found = leftVec.get(right[i]); 
        if(found)
            newVec.push_back(right[i]); 
    }

    return newVec; 
}

vector<long> Table::eval(vector<long> left, string op, vector<long> right){//for logical stuff
    vector<long> recnos; 
    if(op == "and"){//intersect
        recnos = intersection(left, right); 
    }else if(op == "or"){//union
        recnos = combine(left, right); 
    }else{
        cout<<"INVALID OPERAND TYPE\n"; 
    }
    selectedVec = recnos;
    return recnos; 
}

//age, 20, <, age, 17, >, and, lname, Gomex, =, or
//relational --> works with vectors --> gives combined or intersected vectors 
//logical --> works with strings --> gives vec 

vector<long> Table::select_recnos(){
    printVec(selectedVec); 
    return selectedVec; 
}

Table Table::select(vector<string> fields, vector<string> infixCondition){
    Token tok; 
    Queue<Token*> infix = tok.createTokens(infixCondition); 
    ShuntingYard sy(infix); 
    Queue<Token*> post = sy.postfix();
    cout<<"post: "; 
    printQueue(post);  
    return select(fields, post); 
}

Table Table::select(vector<string> fields, string field, string op, string key){
    vector<long> res = eval(field, op, key);  
    Table returnTable = vector_to_table(fields, res);
    selectedVec = res; 
    return returnTable; 
}

Table Table::select(vector<string> fields, Queue<Token*> postFix){ //rpn should prob not have any parentheses 
    //fields --> what to display on table (only fname or only lname)
    Stack<string> toBeEvaluated; 
    Stack<vector<long>> recNums; 
    vector<long> mVec; 
    
    //result vec
    //when evaluated, a vector of recnos will be returned.... 
    while(!postFix.empty()){
        Token* popped = postFix.pop(); 
        int type = popped->getType(); 
        string tokVal = popped->getToken(); 
        //cout<<"popped: "<<tokVal<<endl; 
       // cout<<"post fix stack: "; 
       // printQueue(postFix); 

        if(type == RELATIONAL_TYPE){//relational, logical
            if(!toBeEvaluated.empty()){ //prob won't be empty 
               // cout<<"inside relational\n"; 
                string key = toBeEvaluated.pop(); //first pop key, second pop field name
                //cout<<"key: "<<key<<endl; 
                string field = toBeEvaluated.pop(); 
                //cout<<"field: "<<field<<endl; 
                vector<long> receivedNums = eval(field, tokVal, key); //popped at this point should be the operator
                //cout<<"recs: "; 
                //printVec(receivedNums); 
                recNums.push(receivedNums); 
                
                //then send it into evaluate
            }
        }
        else if(type == LOGICAL_TYPE){
            if(!recNums.empty()){
                //cout<<"inside logical\n"; 
                vector<long> left = recNums.pop(); 
                vector<long> right = recNums.pop(); 
                vector<long> received = eval(left, tokVal, right);
                //cout<<"received recs: "; 
                //printVec(received);  
                recNums.push(received); 
                //then do the intersect or combine for logcial  evals
            }
        }
        else{//a regualr expession
            toBeEvaluated.push(tokVal); //push the string val into stack
        }
    }

    vector<long> res = recNums.pop(); 
    selectedVec = res; 
    Table returnTable = vector_to_table(fields, res);
    return returnTable; 
}



void Table::print_table() const{ 
    FileRecord recordedFiles;  
    fstream aFile; 
    open_fileRW(aFile, filName.c_str()); 
    
    int i= 0;
    int bytes = recordedFiles.read(aFile, i);
    while (bytes>0){
        vector<string> rec = recordedFiles.get_record(); 
        cout<<i; 
        for(int i = 0; i < rec.size(); i++){
            cout<<setw(25)<<rec[i];  
        }
        cout<<endl; 
        bytes = recordedFiles.read(aFile, ++i);
    }
    aFile.close();
}

Table Table::vector_to_table(vector<string> fields, vector<long> recnos){ 
    FileRecord recordedFiles; 
    string name = "temp_" + to_string(serial) + ".bin"; 
    Table returnTable(name.c_str(), fields); 
    fstream aFile; 
    open_fileRW(aFile, filName.c_str()); 
    for(int i = 0; i < recnos.size(); i++){
        vector<string> pushThis; 
        recordedFiles.read(aFile, recnos[i]); 
        vector<string> data = recordedFiles.get_record(); 
        for(int i = 0; i < fields.size(); i++){
            int index = ourFields.get(fields[i]); //getting the part of data we want
            pushThis.push_back(data[index]); 
        }
        returnTable.insert_into(pushThis); 
    }
    aFile.close();
    return returnTable; 
}


Table Table::select_all(){ 
    return select_all(fields); 
}

Table Table::select_all(vector<string> fields){ 
    //cout<<"inside select all\n"; 
    vector<long> recs; 
    for(MMap<string,long>::Iterator beg = mTable[0].begin(); beg != mTable[0].end(); beg++){
        MPair<string,long> received = *beg; 
        recs = combine(recs, received.value_list); 
    }
    selectedVec = recs;
    return vector_to_table(fields, recs); 
}

#endif