#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "../../includes/table/table.h"



bool test_relational(bool debug){
  if(debug){
    vector<string> condition; 
    vector<string> fields = {"fname", "lname", "age", "bounty", "devilfruit"}; 
    Table mTable("one_piece_chars", fields); 

    vector<string> info = {"Roronoa", "Zoro", "19", "1,000,000", "no"}; 
    mTable.insert_into(info); 
    info = {"Vinsmoke", "Sanji", "19", "999,000", "no"}; 
    mTable.insert_into(info); 
    info = {"Luffy", "Monkey D", "17", "9,000,000", "yes"}; 
    mTable.insert_into(info); 
    info = {"Akagami", "Shanks", "37", "10,000,000", "no"};
    mTable.insert_into(info);  
    info = {"Mihawk", "Takemeno", "39", "8,000,000", "no"}; 
    mTable.insert_into(info); 
    info = {"Portgas D.", "Ace", "21", "300,027,000", "yes"}; 
    mTable.insert_into(info); 
    info = {"Cavendish", "Hakuba", "18", "333,000", "no"}; 
    mTable.insert_into(info); 
    info = {"Trafalgar D.", "Water Law", "25", "11,271,000", "yes"}; 
    mTable.insert_into(info); 
    info = {"Sabo", "D. Kun", "22", "10,000,000", "yes"}; 
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


    condition = {"age", "<=", "22"}; //less than equal NOT working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 


    condition = {"age", ">=", "33"}; //less than NOT working
    cout<<"select: "<<condition<<endl; 
    cout<<mTable.select(fields, condition)<<endl; 
    cout<<"recnos: "<<endl; 
    mTable.select_recnos(); 
  }
}


TEST(TEST_RELATIONAL, testRelational){
  EXPECT_EQ(1, test_relational(true)); 
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

