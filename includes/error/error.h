#ifndef ERROR_H 
#define ERROR_H 

#include "../../includes/bplustree/bplustree.h"
#include "../../includes/tokenizer/constants.h"
#include <vector>
#include <fstream> 

const int MAKE_TABLE_NAME = 3; 
const int INSERT_TABLE_NAME = 8;
const int GET_FIELD_FROM = 19; 
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
        Map<string,int> relationalTypes; //a map of relational operators, a map of logical operators, a map of 
        Map<string,int> logicalTypes; 
        bool hasError; 
        string errorMessage;
        //helper functions 
        void makeTableError(int lastSuccessState); 
        void insertError(int lastSuccessState); 
        void selectError(int lastSuccessState);
        void getError(int lastSuccessState); 
        void generalErrors(int lastSuccessState); 
        void increment(int* typesArr, string tok); 

        bool searchFile(string fileName, string findThis); 
        void extract(); 

        string command; 
        string tableName; 
        vector<string> values; 
        vector<string> cols; 
        vector<string> condition; 
        vector<string> fields; 
};

Error_Handler::Error_Handler(){
    init_token_types(); 
    hasError = false; 
}

Error_Handler::Error_Handler(MMap<string, string> stateTree){
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
        condition = statementTree.get("conditon"); 
}

bool Error_Handler::inError(){
    return hasError;
}

//maybe an extract method --> extracts everything and checks it 

void Error_Handler::generalErrors(int lastSuccessState){
    if(statementTree.empty()){//this is the problem right here 
        hasError = true; 
        errorMessage = "ERROR: no command or invalid command was entered. Remember all commands must be typed in lowercase\n"; 
        return; 
    }
    else if(tableName == "" || lastSuccessState == TABLE || lastSuccessState == INTO || lastSuccessState == FROM){
        hasError = true; 
        errorMessage = "ERROR: table name is missing/invalid. Please remember you cannot have a keyword as your table name. For a list of keywords, enter '?'"; 
        
    }
    else if((command == "select" || command == "insert" || command == "get") && !foundTableName(tableName)){
        errorMessage = "ERROR: trying to insert/select/get fields from a non-existent table. Please double-check your spelling and capitalization\n"; 
        hasError = true; 
    }
}

void Error_Handler::makeTableError(int lastSuccessState){
    if(lastSuccessState == MAKE){
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'table' after make\n"; 
    }
    else if(lastSuccessState == MAKE_TABLE_NAME && !hasError){//3 being the table name state
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'fields' after your table name\n"; 
    }
    else if(command == "make" && !statementTree.contains("col") && !hasError){
        hasError = true; 
        errorMessage = "ERROR: missing field names. Please enter at least one field name when making a table\n"; 
    }
    else if(command == "make" && foundTableName(tableName)){ //table already exists 
        hasError = true; 
        errorMessage = "ERROR: table already exists. If you'd like to overwrite the table, please delete the file and then call the make command\n"; 
    }
}

void Error_Handler::insertError(int lastSuccessState){
    if(lastSuccessState == INSERT){
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'into' after insert\n"; 
    }
    else if(lastSuccessState == INSERT_TABLE_NAME && !hasError){
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'values' after your table name\n"; 
    }
    else if(lastSuccessState == VALUES && !hasError){
        hasError = true; 
        errorMessage = "ERROR: missing values. Please insert at least one value when inserting into table\n"; 
    }
}

void Error_Handler::selectError(int lastSuccessState){
    if(lastSuccessState == SELECT){
        hasError = true; 
        errorMessage = "ERROR: missing fields. Please enter at least one field when selecting from the table\n"; 
    }
    else if(lastSuccessState == ALL || lastSuccessState == 17){ //17 is a field state
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'from' after your fields"; 
    }
    else if(lastSuccessState == 201){
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'where' after your table name\n"; 
    }
    else if(statementTree.contains("where") && !statementTree.contains("condition")){
        hasError = true; 
        errorMessage = "ERROR: missing a condition after 'where'\n"; 
    }

    if(statementTree.contains("condition")){//we always check the condition whenever we have it no matter what
        checkCondition(condition); 
    }
}

void Error_Handler::getError(int lastSuccessState){
    if(lastSuccessState == GET){
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'fields' after 'get'\n"; 
    }
    else if(command == "get" and lastSuccessState == GET_FIELD_FROM){//field before from state
        hasError = true; 
        errorMessage = "ERROR: missing keyword 'from' after fields\n"; 
    }
}

bool Error_Handler::checkForErrors(int lastSuccessState){ //error checker
    generalErrors(lastSuccessState); //checking for general errors 
    makeTableError(lastSuccessState); //checking for error in make table path
    insertError(lastSuccessState); //checking for error in insert path 
    selectError(lastSuccessState); //checking for error in select path
    getError(lastSuccessState); //checking for error in get path
    return hasError; 
}

//2nd round of error checking
bool Error_Handler::checkForErrors(vector<string> recFields){//called in sql --> for insert and select
    vector<string> values = statementTree.get("values"); 

    if(command == "select" && !fields.empty() && !hasError){
        string invalidField; 
        hasError = !checkFields(recFields, invalidField); //checks fields to make sure all
        if(hasError)
            errorMessage = "ERROR: " + invalidField + " is not a valid field name.\n"; 
    }
    if(command == "insert" && values.size() != recFields.size()){
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