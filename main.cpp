#include <iostream>
#include <iomanip>

#include "includes/sql/sql.h"


using namespace std;


int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;
    const vector<string> command_list = {

/*00*/     "make table employee fields  last,       first,         dep,      salary, year",
/*01*/     "insert into employee values Blow,       Joe,           CS,       100000, 2018",
/*03*/     "insert into employee values Blow,       Joe,           CS,       100000, 2018",
/*02*/     "insert into employee values Blow,       JoAnn,         Physics,  200000, 2016",
/*03*/     "insert into employee values Johnson,    Jack,          HR,       150000, 2014",
/*04*/     "insert into employee values Johnson,    \"Jimmy\",     Chemistry,140000, 2018", 
/*12*/     "select last, first, salary from employee",
/*14*/     "select * from employee where last = Johnson",
/*15*/     "select * from employee where last=Blow and major=\"JoAnn\""
}; 

SQL sql1; 

for(int i = 0; i < command_list.size(); i++){
    cout<<"com: "<<command_list[i]<<endl;
    cout<<sql1.command(command_list[i])<<endl;  
}


    /*string command;
    SQL sql1; 

    while(true){
        cout<<"Please enter a command: \n";
        cout<<"or if you'd like to quit: please type exit\n"; 
        getline(cin, command); 
        cout<<"your command: "<<command<<endl; 
        if(command == "exit")
            break;   
        cout<<sql1.command(command)<<endl; 
    }*/
    
    cout << "\n\n\n=====================" << endl;
    return 0;
}
