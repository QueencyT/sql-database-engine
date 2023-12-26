#ifndef SQL_H 
#define SQL_H 
#include<iostream>
#include <string>
#include "../../includes/parser/parser.h"
#include "../../includes/table/table.h"
#include "../../includes/error/error.h"

using namespace std; 

class SQL{
    public: 
    Table command(string com); 
    vector<long> select_recnos(); 
    bool inError(){return errorHandler.inError();}

    private: 
    Table mTable; 
    Parser parser; 
    vector<string> allFields; 
    MMap<string,string> statementTree; 
    Error_Handler errorHandler; 

    Table selectCommand(string tableName);
    Table makeCommand(string tableName); 
    Table insertCommand(string tableName);
    Table emptyTable();

    //boolean helper functions 
    bool hasCondition(); 
    bool selectAll();
    bool statementInvalid(); 

    vector<string> getFieldsCommand(string tableName);

    //
    void printFields(vector<string> fields){
        cout<<"fields: "; 
        for(int i = 0; i < fields.size(); i++){
            cout<<fields[i]<<" ";
        }
        cout<<endl; 
    } 
}; 

vector<long> SQL::select_recnos(){
    return mTable.select_recnos();
}

bool SQL::statementInvalid(){
    errorHandler = Error_Handler(statementTree); 
    int lastSuccessState = parser.getLastState(); 
    errorHandler.checkForErrors(lastSuccessState); 
    return errorHandler.inError(); 
}

//what about empty commands
Table SQL::command(string com){
    Table returnTable; 
    parser.set_string(com); 
    statementTree = parser.parse_tree(); 

    if(statementInvalid()){
        cout<<errorHandler.getErrorMessage(); 
        return emptyTable(); 
    }
    
    string command = statementTree.get("command")[0];
    string tableName = statementTree.get("table_name")[0];

    if(command == "make" || command == "create"){
        errorHandler.addTableName(tableName); 
        returnTable = makeCommand(tableName); 
    }
    else if(command == "insert"){
       returnTable =  insertCommand(tableName); 
    }else if(command == "select"){ //if * or age,lname, 
        returnTable = selectCommand(tableName);  
    } 
    else if(command == "get"){
        vector<string> fields = getFieldsCommand(tableName); 
        printFields(fields); 
        return emptyTable();
    }

    return returnTable; 
}

Table SQL::makeCommand(string tableName){
    vector<string> col = statementTree.get("col");
    allFields = col; 
    mTable = Table(tableName.c_str(), col); //creating table //for now 
    return mTable; 
}

Table SQL::insertCommand(string tableName){
    mTable = Table(tableName.c_str()); 
    allFields = mTable.getFields(); 
    errorHandler.checkForErrors(allFields); 

    if(errorHandler.inError()){
        cout<<errorHandler.getErrorMessage(); 
        return emptyTable();
    } 

    vector<string> vals = statementTree.get("values");
    mTable.insert_into(vals); 
    return mTable; 
}

Table SQL::selectCommand(string tableName){ //trying to select from a table that does not exist
    vector<string> fields = statementTree.get("fields");  
    mTable = Table(tableName.c_str());
    allFields = mTable.getFields(); 
    
    errorHandler.checkForErrors(allFields); 
    if(errorHandler.inError()){
        cout<<errorHandler.getErrorMessage(); 
        return emptyTable();
    } 

    if(selectAll() && !hasCondition()){
        cout<<"select all with no condition\n"; 
        return mTable.select_all(allFields);  
    }
    else if(selectAll() && hasCondition()){
        cout<<"select all with condition\n"; 
        vector<string> condition = statementTree.get("condition");
        return mTable.select(allFields, condition);
    }
    else if(!selectAll() && !hasCondition()){
        cout<<"regular select with no condition\n"; 
        return mTable.select_all(fields); 
    }
    else{//if not select all and has a condition
        cout<<"regular select with condition\n"; 
        vector<string> condition = statementTree.get("condition");
        return mTable.select(fields, condition); 
    }
}

vector<string> SQL::getFieldsCommand(string tableName){//get fields from student --> could make a custom SQL command
    vector<string> fields; 
    if(errorHandler.foundTableName(tableName)){
        Table temp(tableName.c_str()); 
        return temp.getFields(); 
    }
    return fields; 
} //table name --> gets the fields of a tablename

Table SQL::emptyTable(){
    string mt = "empty table.txt"; 
    vector<string> emptyF = {"empty"};
    Table empty(mt.c_str(), emptyF); 
    return empty; 
}

bool SQL::hasCondition(){
    return statementTree.contains("where"); 
}

bool SQL::selectAll(){
    return (statementTree.get("fields")[0] == "*"); 
}
#endif