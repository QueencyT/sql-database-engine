#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../includes/table/table.h"
#include "../../includes/sql/sql.h"






bool test_relational(bool debug){ //working so far 
  if(debug){
    vector<string> condition; 
    vector<string> fields = {"fname", "lname", "age", "bounty", "devilfruit"}; 
    Table mTable("one_piece_chars", fields); 

    vector<string> info = {"Roronoa", "Zoro", "19", "1000000", "no"}; 
    mTable.insert_into(info); 
    info = {"Vinsmoke", "Sanji", "19", "999000", "no"}; 
    mTable.insert_into(info); 
    info = {"Luffy", "Monkey D", "17", "9000000", "yes"}; 
    mTable.insert_into(info); 
    info = {"Akagami", "Shanks", "37", "10000000", "no"};
    mTable.insert_into(info);  
    info = {"Mihawk", "Takemeno", "39", "8000000", "no"}; 
    mTable.insert_into(info); 
    info = {"Portgas D.", "Ace", "21", "300027000", "yes"}; 
    mTable.insert_into(info); 
    info = {"Cavendish", "Hakuba", "18", "333000", "no"}; 
    mTable.insert_into(info); 
    info = {"Trafalgar D.", "Water Law", "25", "11271000", "yes"}; 
    mTable.insert_into(info); 
    info = {"Sabo", "D. Kun", "22", "10000000", "yes"}; 
    mTable.insert_into(info); 

    cout<<"table: \n"; 
    cout<<mTable<<endl; 

    condition = {"age", ">", "37"}; //greater than is working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"lname", "=", "D. Kun"}; //greater than is working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"age", "<", "18"}; //less than is working //does not include 18 itself which is correct 
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 


    condition = {"age", "<=", "21"}; //less than equal NOT working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 


    condition = {"age", ">=", "33"}; //less than NOT working
    cout<<"select: "<<condition<<endl; 
    //vector<string> last = {"lname"}; 
    cout<<mTable.select(fields, condition)<<endl; 
    //cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 
  }

  if(debug){
    string s1 = "make table student fields fname, lname, major, age"; 
    string s2 = "insert into student values Flo, Yao, CS, 20"; 
    string s3 = "insert into student values \"Flo\", \"Jackson\", Math,21"; 
    string s4 = "insert into student values Calvin, Woo, Physics,22"; 
    string s5 = "insert into student values \"Anna Grace\", \"Del Rio\", CS, 22"; 
    vector<string> commands; 
    commands.push_back(s1);  
    commands.push_back(s2); 
    commands.push_back(s3); 
    commands.push_back(s4); 
    commands.push_back(s5); 

    SQL sql; 
    for(int i = 0; i < commands.size(); i++){
      sql.command(commands[i]); 
    }

    string command = "select * from student"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where lname = \"Del Rio\""; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where lname = \"Does Not Exist\""; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where lname > Yang"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 


    cout<<"--------------------------------------- GREATER THAN --------------------------------\n"; 

    command = "select * from student where age > 50"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where age > 53"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();


    command = "select * from student where age > 54"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    cout<<"--------------------------------------- GREATER THAN EQUAL --------------------------------\n"; 


    command = "select * from student where lname >= Yang"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();


    /*command = "select * from student where last >= Jack"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();*/

    cout<<"--------------------------------------- LESS THAN --------------------------------\n"; 

    command = "select * from student where lname < Jackson"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where age < 20"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where age < 19"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    cout<<"--------------------------------------- LESS THAN EQUAL --------------------------------\n"; 

    command = "select * from student where lname <= Smith"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();
  }
  return true; 
}



bool test_logical(bool debug){ //working so far --> seems to be working.........//if relational prob just testing two expressions
  if(false){//at least 14 records
    vector<string> condition; 
    vector<string> fields = {"fname", "lname", "age", "bounty", "devilfruit"}; 
    Table mTable("one_piece_chars", fields); 

    vector<string> info = {"Roronoa", "Zoro", "19", "88", "no"}; 
    mTable.insert_into(info); 
    info = {"Vinsmoke", "Sanji", "19", "87", "no"}; 
    mTable.insert_into(info); 
    info = {"Luffy", "Monkey D", "17", "90", "yes"}; 
    mTable.insert_into(info); 
    info = {"Akagami", "Shanks", "37", "99", "no"};
    mTable.insert_into(info);  
    info = {"Mihawk", "Takemeno", "39", "80", "no"}; 
    mTable.insert_into(info); 
    info = {"Portgas D.", "Ace", "21", "30", "yes"}; 
    mTable.insert_into(info); 
    info = {"Cavendish", "Hakuba", "18", "33", "no"}; 
    mTable.insert_into(info); 
    info = {"Trafalgar D.", "Water Law", "25", "11", "yes"}; 
    mTable.insert_into(info); 
    info = {"Sabo", "D. Kun", "22", "10", "yes"}; 
    mTable.insert_into(info); 

    cout<<"table: \n"; 
    cout<<mTable<<endl; 

    condition = {"age", ">", "19", "or", "lname", "=", "Monkey D"}; //or is working rn
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"age", ">", "15", "and", "lname", "=", "Monkey D"}; //or is working rn
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"bounty", ">", "78"}; //not working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"age", ">", "35", "or", "bounty", ">", "78", "and", "devilfruit", "=", "no"}; //not working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"age", ">", "35", "or", "age", "<", "18"}; //not working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 

    condition = {"age", ">", "21", "and", "age", "<", "30"}; //not working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 
  }

  if(debug){
    string s1 = "make table student fields fname, lname, major, age"; 
    string s2 = "insert into student values Flo, Yao, CS, 20"; 
    string s3 = "insert into student values \"Flo\", \"Jackson\", Math,21"; 
    string s4 = "insert into student values Calvin, Woo, Physics,22"; 
    string s5 = "insert into student values \"Anna Grace\", \"Del Rio\", CS, 22"; 
    vector<string> commands; 
    commands.push_back(s1);  
    commands.push_back(s2); 
    commands.push_back(s3); 
    commands.push_back(s4); 
    commands.push_back(s5); 

    /*
    0                      Flo                      Yao                       CS                       20
    1                     Flo                  Jackson                     Math                        21
    2                   Calvin                      Woo                  Physics                       22
    3               Anna Grace                  Del Rio                       CS                       22
    */

   //203
    SQL sql; 
    for(int i = 0; i < commands.size(); i++){
      sql.command(commands[i]); 
    }

    string command = "select * from student"; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where fname = \"Flo\" and lname = \"Yao\""; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where fname = \"Flo\" or lname = \"Jackson\""; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where fname = \"Flo\" or major = CS and age <= 23"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where lname = \"Yang\" or major = CS and age < 23 or lname = Jackson"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();


    command = "select * from student where age < 30 and major = CS or major = Physics and lname = Jackson"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where age > 30 and major=Art or major = Physics and lname = Woo"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 
  }
}

bool test_parentheses(bool debug){
  string s1 = "make table student fields fname, lname, major, age"; 
    string s2 = "insert into student values Flo, Yao, CS, 20"; 
    string s3 = "insert into student values \"Flo\", \"Jackson\", Math,21"; 
    string s4 = "insert into student values Calvin, Woo, Physics,22"; 
    string s5 = "insert into student values \"Anna Grace\", \"Del Rio\", CS, 49"; 
    string s6 = "insert into student values \"Anna Kat\", \"The Bat\", Art, 33"; 
    string s7 = "insert into student values Lilli, Sutton, Communications, 34"; 
    string s8 = "insert into student values Oliver, Knox, Math, 25"; 
    string s9 = "insert into student values Johnathan, Salinas, Biology, 18";
    string s10 = "insert into student values Justin, Wang, History, 19"; 

    vector<string> commands; 
    commands.push_back(s1);  

    //insertions
    commands.push_back(s2); 
    commands.push_back(s3); 
    commands.push_back(s4); 
    commands.push_back(s5);
    commands.push_back(s6); 
    commands.push_back(s7);
    commands.push_back(s8); 

    SQL sql; 
    for(int i = 0; i < commands.size(); i++){
      sql.command(commands[i]); 
    }

    cout<<"full table\n"; 
    cout<<sql.command("select * from student")<<endl; 

  if(false){
    cout<<"full table\n"; 
    cout<<sql.command("select * from student")<<endl; 

    
    string command; 
    command = "select * from student where age < 30 and ((major = CS or major = Physics) and (lname < Y))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (fname = \"Anna Grace\" and lname = \"Del Rio\")) or (age >= 22))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 


    //professor tests
    command = "select * from student where (age <30 and age > 20) and ((major = CS or major = Physics) or (lname < M))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where ((age < 30 and age > 20) and major = Communications) or ((major = CS or major = Physics))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where ((age < 25 and age > 20) or major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where age < 25 or (age > 20 and major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (age < 25 or age > 20) and major = Communications"; 
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (age < 25 and age > 20) and major = Communications"; //will give non-existent
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= N))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); 

    command = "select * from student where (age < 25 and age > 20) and (lname > D and lname <= N) or (major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where (age < 25 and age > 20) and (lname > J) or (major = Math)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    command = "select * from student where ((age < 20 and age > 30)) and ((major = Art) or (major = Math))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();


  }

  if(debug){
    
    string command = "select * from student where ((age < 25 and age > 20) or major = Communications)";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos();

    /*string command = "select * from student where ((age < 25 and age > 20) or major = Communications) or ((lname > D and lname <= N))";
    cout<<"command: "<<command<<endl; 
    cout<<sql.command(command)<<endl; 
    sql.select_recnos(); */

  }
}

bool testTokenize(bool debug){
  if(debug){
    STokenizer tokenizer; 
    tokenizer.set_string("\"Teresae Mae\""); 
    string val; 
    tokenizer >> val; 
    cout<<"val: "<<val<<endl; 
  }
}

bool test_combine(bool debug){ //combination and intersection functions are probably working
  if(debug){
    //26 78 51 3 14 93 58 30 72 62
    //6 89 33 5 27 85 77 79 50 66
    Table mTable;
    vector<long> vec1 = {26, 78, 51, 3, 14, 93, 58, 30, 72, 62}; 
    vector<long> vec2 = {6, 89, 33, 5, 27, 85, 77, 79, 50, 66}; 

    cout<<"intersection of: \n"; 
    cout<<"vec1: "; 
    mTable.printVec(vec1); 
    cout<<"vec2: "; 
    mTable.printVec(vec2); 
    //vector<long> res = mTable.intersection(vec1, vec2); 
    //mTable.printVec(res); 

    //1 11 5 14 10 9 13 15 3 12
    //5 15 0 1 9 14 3 8 11 6

    vec2 = {1, 11, 5, 14, 10, 9, 13, 15, 3, 12}; 
    vec1 = {5, 15, 0, 1, 9, 14, 3, 12}; 

    cout<<"intersection of: \n"; 
    cout<<"vec1: "; 
    mTable.printVec(vec1); 
    cout<<"vec2: "; 
    mTable.printVec(vec2); 
    //res = mTable.intersection(vec1, vec2); 
    //mTable.printVec(res); 
    
  }
}


TEST(TEST_RELATIONAL, testRelational){
  EXPECT_EQ(1, test_relational(false)); 
}

TEST(TEST_LOGICAL, testLogical){
  EXPECT_EQ(1, test_logical(false)); 
}

TEST(TEST_COMBINE, testCombine){
  EXPECT_EQ(1, test_combine(false)); 
}

TEST(TEST_PARENTHESES, testParen){
  EXPECT_EQ(1, test_parentheses(true)); 
}

TEST(TEST_TOKENIZE, testTokenize){
  EXPECT_EQ(1, testTokenize(false)); 
}
bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

