#ifndef SQL_H 
#define SQL_H 
#include<iostream>
#include <string>
#include "../../includes/parser/parser.h"
#include "../../includes/table/table.h"

using namespace std; 

class SQL{
    public: 
    Table command(string com); 
    vector<long> select_recnos(); 
    private: 
    Table mTable; 
    Parser parser; 
    vector<string> allFields; 
    MMap<string,string> statementTree; 
    Table selectCommand(string tableName);
    Table makeCommand(string tableName); 
    Table insertCommand(string tableName); 
    //boolean helper functions 
    bool hasCondition(); 
    bool selectAll(); 

    vector<string> printFields(vector<string> f){
        for(int i = 0; i < f.size(); i++){
            cout<<f[0]<<" "; 
        }
        cout<<endl; 
    }
}; 

vector<long> SQL::select_recnos(){
    return mTable.select_recnos();
}

Table SQL::command(string com){
    parser.set_string(com); 
    statementTree = parser.parse_tree(); 
    string command = statementTree.get("command")[0]; //will always have a t
    string tableName = statementTree.get("table_name")[0];
    Table returnTable; 

    if(command == "make" || command == "create"){
        returnTable = makeCommand(tableName); 
    }
    else if(command == "insert"){
        cout<<"SQL - inserting\n";
       returnTable =  insertCommand(tableName); 
    }else if(command == "select"){ //if * or age,lname, 
        returnTable = selectCommand(tableName);  
    } 

    //cout<<"table\n"; 
    //cout<<returnTable<<endl; 
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
   // cout<<"map: 0: "<<endl; 
   // cout<<mTable.mTable[1]<<endl; 

    vector<string> vals = statementTree.get("values");
    mTable.insert_into(vals);
    //cout<<"after map: "<<endl;  
   // cout<<mTable.mTable[1]<<endl; 
    return mTable; 
}

Table SQL::selectCommand(string tableName){
    vector<string> fields = statementTree.get("fields");  
    mTable = Table(tableName.c_str());
    allFields = mTable.getFields(); 

    cout<<"statement tree: \n"; 
    cout<<statementTree<<endl; 

    cout<<"received table\n"; 
    cout<<mTable<<endl; 
    cout<<"mTable map[0]: "<<endl; 
    cout<<mTable.mTable[0]<<endl; 

    cout<<"fields: "<<allFields.size()<<endl; 

    if(selectAll() && !hasCondition()){
        cout<<"select all with no condition\n"; 
        cout<<"allFields: "<<allFields[0]<<endl; 
        cout<<"size fields: "<<allFields.size()<<endl;  
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

bool SQL::hasCondition(){
    return statementTree.contains("where"); 
}

bool SQL::selectAll(){
    return (statementTree.get("fields")[0] == "*"); 
}
#endif