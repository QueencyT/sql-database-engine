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
    Table select_command(); 
}; 

vector<long> SQL::select_recnos(){
    return mTable.select_recnos();
}

Table SQL::command(string com){
    parser.set_string(com); 
    statementTree = parser.parse_tree(); 

    vector<string> command = statementTree.get("command"); //will always have a t
    vector<string> tableName = statementTree.get("table_name");
    Table returnTable; 

    if(command[0] == "make" || command[0] == "create"){
       vector<string> col = statementTree.get("col");
       allFields = col; 
       mTable = Table(tableName[0].c_str(), col); //creating table //for now 
    }
    else if(command[0] == "insert"){
        mTable = Table(tableName[0].c_str()); 
        vector<string> vals = statementTree.get("values");
        mTable.insert_into(vals); 
    }else if(command[0] == "select"){ //if * or age,lname, 
        Table tab = select_command(); 
        cout<<"table\n"; 
        cout<<tab<<endl; 
        return tab; 
    } 
    return mTable; 
}

Table SQL::select_command(){
    //assuming at this point 
        string tableName = statementTree.get("table_name")[0]; 
        vector<string> fields = statementTree.get("fields");  
        mTable = Table(tableName.c_str());
        allFields = mTable.getFields(); 
        if(fields.at(0) == "*" && !statementTree.contains("where")){
            cout<<"select all with no condition\n"; 
            return mTable.select_all(allFields);  
        }
        else if(fields.at(0) == "*" && statementTree.contains("where")){
            cout<<"select all with conditon\n"; 
            vector<string> condition = statementTree.get("condition"); 
            return mTable.select(allFields, condition);
        }
        else if(fields.at(0) != "*" && !statementTree.contains("where")){
            cout<<"regular select with no conditions\n"; 
            return mTable.select_all(fields); 
        }
        else{
            vector<string> condition = statementTree.get("condition");
            return mTable.select(fields, condition); 
        }
}
//command selector --> if(command == make) if(command = insert) if(command = select)
#endif