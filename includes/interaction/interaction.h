#ifndef INTERACTION_H 
#define INTERACTION_H 

#include "../../includes/sql/sql.h"
#include "../../includes/parser/parser.h"
#include <stdlib.h> 
#include <windows.h>
#include <conio.h>

 


using namespace std; 

class Interaction{
    public: 
        void start(); 
    private: 
    SQL sql; 
    bool endProgram = false; 

    //cout helper functions
    void printHelp(); 
    void splashScreen(); 
    void helpSplashScreen(); 

    void printMakeGuide();
    void printSelectGuide(); 
    void printInsertGuide(); 
    void printGetGuide(); 
    void decider();
    void decider(string command); 
    void ansDecider(char ans);
};

void Interaction::helpSplashScreen(){
    cout<<endl; 
    system("cls"); 
    cout<<"                           THE HELP DESK                   \n"; 
    cout<<endl; 
    cout<<"                   /\\__/\\      (\\__/)    ()___()\n"; 
    cout<<"                  ( .  . )     (.  .)    ( . . )\n"; 
    cout<<"                  <       >   <      >   <     >\n";
    cout<<"          +-----------------------------------------------+\n"; 
    cout<<endl; 
    cout<<"                            SYNTAX RULES\n"; 
    cout<<"                commands must be typed in lowercase\n"; 
    cout<<"            table name and field name cannot be a keyword\n"; 
    cout<<endl; 
    cout<<"                              KEYWORDS\n";
    cout<<"   create,make,table,insert,into,*,select,from,where,values,fields\n";
    cout<<endl; 
    cout<<"     +---------------------------------------------------------+\n"; 
    cout<<"                           COMMAND INFO\n";
    cout<<endl; 
    cout<<"               'MAKE TABLE' COMMAND INFO - PRESS M\n"; 
    cout<<"                  'SELECT' COMMAND INFO - PRESS S\n"; 
    cout<<"               'INSERT INTO' COMMAND INFO - PRESS I\n"; 
    cout<<"               'GET FIELDS' COMMAND INFO - PRESS G\n"; 
    cout<<"              SEE THE GUIDE FOR ALL COMMANDS - PRESS A\n"; 
    cout<<"                  EXIT BACK TO PROGRAM - PRESS E\n";
    cout<<endl; 
}

void Interaction::printMakeGuide(){
    cout<<"                                       +-----------------------------------------------------------------+\n"; 
    cout<<"                                                                MAKE TABLE COMMAND\n";
    cout<<"                               make [table name] fields [field names] - makes a table with the given field names\n"; 
    cout<<"                                                    example: make table champions fields name, age\n"; 

}

void Interaction::printSelectGuide(){
    cout<<"                                       +-----------------------------------------------------------------+\n"; 
    cout<<"                                                                 SELECT COMMAND\n";
    cout<<"                                         select * from [table name]- selects the entire given table\n"; 
    cout<<"                                                       example: select * from champions\n";
    cout<<endl; 
    cout<<"                                 select [field names] - selects the table but only prints out the given fields \n"; 
    cout<<"             example: select age,fname from champions - selects all the records in champions but only prints out the records' age and fname\n"; 
    cout<<"     example: select age, fname, lname from champions - selects all the records in champions but only prints out the records' age,fname, and lname\n"; 
    cout<<endl; 
    cout<<"                    select  ... from [table name] where [condition] - selects all the table where the given condition is true\n";
    cout<<"                                           example: select * from champions where name = aphelios\n"; 
}

void Interaction::printInsertGuide(){
    cout<<"                                       +-----------------------------------------------------------------+\n"; 
    cout<<"                                                                 INSERT COMMAND\n";
    cout<<"                                            insert into - inserts some values into a given table\n"; 
    cout<<"                                           example: insert into character values Roronoa, Zoro, 21\n"; 
}

void Interaction::printGetGuide(){
    cout<<"                                       +-----------------------------------------------------------------+\n"; 
    cout<<"                                                               GET FIELDS COMMAND\n";
    cout<<"                            get fields from [table name] - gets the field names of the indicated table if the table exists.\n"; 
    cout<<"                                             example: insert into character values Roronoa, Zoro, 21\n"; 
    cout<<"                                       +-----------------------------------------------------------------+\n"; 
}

void Interaction::decider(){
    char userAns; 
    cout<<"                               +--------------------------------------------------------------------------------+\n";
    cout<<"                               |      PRESS H - to go back to help desk | PRESS E - to go back to program       |\n";
    cout<<"                               +--------------------------------------------------------------------------------+\n";
    cout<<">"; 
    cin>>userAns; 
    

    if(userAns == 'E'){
        start(); 
    }
    else if(userAns = 'H'){
        printHelp(); 
    }
}

void Interaction::ansDecider(char ans){
    cout<<endl; 
    system("cls");
    switch(ans){
        case 'M':
            printMakeGuide();
        break; 
        case 'S':
            printSelectGuide();
        break; 
        case 'I':
            printInsertGuide();
        break; 
        case 'G':
            printGetGuide();
        break;
        case 'A':
            printMakeGuide(); 
            printSelectGuide(); 
            printInsertGuide(); 
            printGetGuide(); 
        break;
        case 'E': 
            start(); 
            break;
    }
    if(ans != 'E'){
        cout<<endl; 
        decider();
    }

}

void Interaction::printHelp(){
    char userAns; 
    helpSplashScreen();
    cout<<"ENTER YOUR COMMAND: "; 
    cin>>userAns; 
    ansDecider(userAns);
}


void Interaction::splashScreen(){
    cout<<"+------------------------------------------------------------+\n";
    cout<<"|                        SQL DATABASE:                       |\n";
    cout<<"|    - Make sure to type your commands in all lowercase -    |\n"; 
    cout<<"|         if you'd like to quit: please type 'exit'          |\n"; 
    cout<<"|     if you'd like to see the help menu: please type '?'    |\n"; 
    cout<<"+------------------------------------------------------------+\n";
    cout<<endl; 
    cout<<"   +--------------------+             - MAKE TABLE\n"; 
    cout<<"   |      Available     |             - SELECT\n";
    cout<<"   |     SQL Command    |             - INSERT INTO\n";
    cout<<"   +--------------------+             - GET FIELDS\n"; 
    cout<<"    (\\__/)  ||                    PRESS ? FOR MORE INFO\n"; 
    cout<<"    (.  .)  ||\n"; 
    cout<<"    /     > ||\n";
}

void Interaction::decider(string command){
    if(command == "exit"){
        endProgram = true; 
    }
    else if(command == "?"){
        printHelp(); 
        endProgram = true; 
    }
    else{
        cout<<sql.command(command)<<endl; 
        endProgram = false; 
    }
}

void Interaction::start(){
    string command; 
    splashScreen(); 

    while(!endProgram){
       cout<<"Enter a command: Press exit to end program, press ? for help\n";
       cout<<">"; 
       getline(cin, command); 
       decider(command);
        
        while(!endProgram && sql.inError()){
            cout<<">";
            getline(cin,command); 
            decider(command);
        }
   }
}
#endif