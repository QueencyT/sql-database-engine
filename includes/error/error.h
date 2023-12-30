#ifndef ERROR_H 
#define ERROR_H 

#include "../../includes/bplustree/bplustree.h"
#include "../../includes/tokenizer/constants.h"
#include "../../includes/error/error_constants.h"
#include "../../includes/bplustree/map.h"
#include <vector>
#include <fstream> 

const string table_names = "table_names";  

using namespace std; 

class Error_Handler{
    public: 
        Error_Handler();
        Error_Handler(MMap<string, string> stateTree);

        bool checkForErrors(int lastSuccessState);  
        bool checkForErrors(vector<string> fields); 
        bool checkFields(vector<string> recFields, string& invalidField);
        void checkCondition(vector<string> condition);  
        bool inError();
        void addTableName(string tableName);
        bool foundTableName(string tableName);
        string getErrorMessage(){return errorMessage;}

        void init_token_types(){
            relationalTypes.insert(">=", RELATIONAL_TYPE); 
            relationalTypes.insert("<=", RELATIONAL_TYPE); 
            relationalTypes.insert("=", RELATIONAL_TYPE); 
            relationalTypes.insert("<", RELATIONAL_TYPE); 
            relationalTypes.insert(">", RELATIONAL_TYPE); 
            logicalTypes.insert("and", LOGICAL_TYPE); 
            logicalTypes.insert("or", LOGICAL_TYPE); 
        }

    private:
        MMap<string,string> statementTree; 
        Map<string,int> relationalTypes; 
        Map<string,int> logicalTypes; 
        Map<int,string> errorMap; 
        bool hasError; 
        string errorMessage;

        string command; 
        string tableName; 
        vector<string> values; 
        vector<string> cols; 
        vector<string> condition; 
        vector<string> fields; 

        //helper functions 
        void generalErrors(int lastSuccessState); 
        void increment(int* typesArr, string tok); 
        bool searchFile(string fileName, string findThis); 
        void extract(); 
        void init_errors(); 
};


void Error_Handler::init_errors(){
    //last success state --> error code  // Map<int,string> errorMap; //error code, error message
    errorMap.insert(INVALID_COMMAND_ERROR, "ERROR: no command or invalid command was entered. Remember all commands must be typed in lowercase\n"); //last success state 0
    //make table error path
    errorMap.insert(MISSING_KEYWORD_TABLE_ERROR, "ERROR: missing keyword 'table' after make\n"); //make table errors
    errorMap.insert(MISSING_KEYWORD_FIELDS_ERROR, "ERROR: missing keyword 'fields' after your table name\n"); 
    errorMap.insert(MISSING_FIELD_NAMES_ERROR, "ERROR: missing field names. Please enter at least one field name when making a table\n"); 
    //insert table error path 
    errorMap.insert(MISSING_KEYWORD_INTO_ERROR, "ERROR: missing keyword 'into' after insert\n"); 
    errorMap.insert(MISSING_KEYWORD_VALUES_ERROR, "ERROR: missing keyword 'values' after your table name\n"); 
    errorMap.insert(MISSING_VALUES_ERROR, "ERROR: missing values. Please insert at least one value when inserting into table\n"); 
    //select table error path 
    errorMap.insert(MISSING_FIELDS_ERROR, "ERROR: missing fields. Please enter at least one field when selecting from the table\n"); 
    errorMap.insert(MISSING_KEYWORD_FROM_ERROR, "ERROR: missing keyword 'from' after your fields"); 
    errorMap.insert(MISSING_KEYWORD_WHERE_ERROR, "ERROR: missing keyword 'where' after your table name\n"); 
    errorMap.insert(MISSING_CONDITION_ERROR, "ERROR: missing a condition after 'where'\n"); 
    //get fields error path 
    errorMap.insert(MISSING_KEYWORD_FIELDS_GET_ERROR,"ERROR: missing keyword 'fields' after 'get'\n"); 
    errorMap.insert(MISSING_KEYWORD_FROM_GET_ERROR, "ERROR: missing keyword 'from' after 'fields'\n"); 
}

Error_Handler::Error_Handler(){
    init_errors();
    init_token_types(); 
    hasError = false; 
}

Error_Handler::Error_Handler(MMap<string, string> stateTree){
    init_errors(); 
    init_token_types();
    hasError = false; 
    statementTree = stateTree; 
    extract(); 
}

void Error_Handler::extract(){
    if(statementTree.contains("command"))
        command = statementTree.get("command")[0]; 

    if(statementTree.contains("table_name"))
        tableName = statementTree.get("table_name")[0]; 

    if(statementTree.contains("values"))
        values = statementTree.get("values"); 

    if(statementTree.contains("fields"))
        fields = statementTree.get("fields"); 

    if(statementTree.contains("cols"))
        cols = statementTree.get("cols"); 

    if(statementTree.contains("condition"))
        condition = statementTree.get("condition"); 
}

bool Error_Handler::inError(){
    return hasError;
}

void Error_Handler::generalErrors(int lastSuccessState){  
    if(tableName == "" || lastSuccessState == TABLE || lastSuccessState == INTO || lastSuccessState == FROM){ 
        hasError = true; 
        errorMessage = "ERROR: table name is missing/invalid. Please remember you cannot have a keyword as your table name. For a list of keywords, enter '?'"; 
        
    }
    else if((command == "select" || command == "insert" || command == "get") && !foundTableName(tableName)){
        errorMessage = "ERROR: trying to insert/select/get fields from a non-existent table. Please double-check your spelling and capitalization\n"; 
        hasError = true; 
    }
    else if(command == "make" && foundTableName(tableName)){ 
        hasError = true; 
        errorMessage = "ERROR: table already exists. If you'd like to overwrite the table, please delete the file and then call the make command\n"; 
    }
    else if(!condition.empty()){//we always check the condition whenever we have it no matter what 
        checkCondition(condition); 
    }
}

bool Error_Handler::checkForErrors(int lastSuccessState){ //error checker //ast success state --> error code
    generalErrors(lastSuccessState);

    if(errorMap.contains(lastSuccessState)){
        hasError = true; 
        errorMessage = errorMap.get(lastSuccessState); 
    }

    return hasError; 
}

//2nd round of error checking
bool Error_Handler::checkForErrors(vector<string> recFields){//called in sql --> for insert and select
    vector<string> values = statementTree.get("values"); 

    if(command == "select" && !fields.empty() && !hasError){ //custom
        string invalidField; 
        hasError = !checkFields(recFields, invalidField); //checks fields to make sure all
        if(hasError)
            errorMessage = "ERROR: " + invalidField + " is not a valid field name.\n"; 
    }
    if(command == "insert" && values.size() != recFields.size()){ //custom 
        hasError = true; 
        errorMessage = "ERROR: incorrect number of values. Make sure you are inserting values for all your fields. Also make sure if you want a value to be treated as one value that you must put it in quotes " "\n"; 
    }

    return hasError; 
}

bool Error_Handler::checkFields(vector<string> recFields, string& invalidField){//for sure at this point our fields are not empty
    bool found = true; //either it really is there, so it will never be turned false, or its not there and will be turned false
    if(fields[0] == "*")
        return true; 

    for(int i = 0; i < fields.size(); i++){ 
         invalidField = fields[i]; 
        for(int n = 0; n < recFields.size(); n++){
            if(fields[i] == recFields[n])
                return true; 
        }
    }
    return false; 
}

void Error_Handler::increment(int* typesArr, string tok){
    const int relation = 0, logic = 1, par = 2, symbol = 3; 
    if(relationalTypes.contains(tok)){
        typesArr[relation]++; 
    }
    else if(logicalTypes.contains(tok)){
        typesArr[logic]++; 
    }
    else if(tok == ")" || tok == "("){
        typesArr[par]++; 
    }
    else{
        typesArr[symbol]++; 
    }
}

void Error_Handler::checkCondition(vector<string> condition){
    string tok; 
    int typesArr[4] = {0,0,0,0}; 
    const int relation = 0, logic = 1, par = 2, symbol = 3;  
    string mCondition = " "; 
 
    for(int i = 0; i < condition.size(); i++){
        tok = condition[i]; 
        mCondition+= (condition[i] + " "); 
        increment(typesArr, tok); 
    }

    int relational = typesArr[relation], logical = typesArr[logic], symbols = typesArr[symbol],paren = typesArr[par];

    if(symbols != 2 * relational){
        hasError = true;
        errorMessage = "ERROR: -"  + mCondition + "- is an invalid condition\n";  
    }
    else if(relational != 0 && logical != relational - 1){
        hasError = true; 
        errorMessage = "ERROR: -" + mCondition + "- is an invalid condition\n"; 
    }
    else if(paren % 2 != 0){
        hasError = true; 
        errorMessage = "ERROR: -" + mCondition + "- is an invalid condition. Missing parentheses.\n";  
    }
}

//table of table names
void Error_Handler::addTableName(string tableName){//adds table name to file of table names 
    fstream mStream; 
    string fileName = "table_names"; 
    open_fileRW(mStream, fileName.c_str()); 
    mStream.seekg(0,mStream.end); 
    vector<string> name = {tableName}; 
    FileRecord writer(name); 
    writer.write(mStream); 
    mStream.close();
}

bool Error_Handler::searchFile(string fileName, string findThis){ //the invalid field/name 
    FileRecord recordReader; 
    fstream mStream; 
    open_fileRW(mStream, fileName.c_str());
    int i = 0; 
    int bytes = recordReader.read(mStream, i);
    while (bytes>0){
        vector<string> rec = recordReader.get_record(); 
        if(rec[0] == findThis){
            return true; 
        }
        bytes = recordReader.read(mStream, ++i);
    }
    mStream.close(); 
    return false; 
}

bool Error_Handler::foundTableName(string tableName){//checks to see if table exists or not (been made before>) //could make this more general and make it searchFile hm
    string fileName = "table_names"; 
    return searchFile(fileName, tableName); 
}
#endif