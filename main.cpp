#include <iostream>
#include <iomanip>

#include "includes/sql/sql.h"


using namespace std;


int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;

    SQL sql; 
    string exit; 
    string command; 
    do{
        cout<<"Please enter a command: \n";
        cout<<"or if you'd like to quit: please type exit\n"; 
        getline(cin, command); 
        cout<<"your command: "<<command<<endl;   
        cout<<sql.command(command)<<endl; 
    }
    while(command != "exit"); 
    
    cout << "\n\n\n=====================" << endl;
    return 0;
}
