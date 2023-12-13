#ifndef FILE_RECORD_H 
#define FILE_RECORD_H 

#include <iostream>
#include <cassert>
#include <vector>
#include <string> 
#include <fstream>

using namespace std; 

class FileRecord
{
public:
    FileRecord(); 
    FileRecord(vector<string> data); 

    //when you construct a FileRecord, it's either empty or it
    //  contains a word

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file
    vector<string> get_record(); 


    friend ostream& operator<<(ostream& outs, const FileRecord& r){
        for(int row = 0; row < r.MAX_ROWS && r._record[row][0] != '\0'; row++){
            for(int col = 0; r._record[row][col] != '\0'; col++){
                outs<<r._record[row][col]; 
            }
            outs<<endl;
        }
        return outs; 
    }

    static const int MAX = 100;
    static const int MAX_ROWS = 20;
    static const int MAX_COLS = 100;
    char _record[MAX_ROWS][MAX_COLS + 1]; //how big should the 2d arry be?

private:
    long recNum; 
    void init_array(); 
};


void FileRecord::init_array(){
    for(int i = 0; i < MAX_ROWS; i++){
        for(int n = 0; n < MAX_COLS + 1; n++){
            _record[i][n] = '\0';
        }
    }
}


FileRecord::FileRecord(){
    recNum = 0;
    init_array(); 
}

FileRecord::FileRecord(vector<string> data){ //vector of all the fields to write I suppose? //the data //last name, first name, anime
    assert(data.size() < MAX_ROWS); //v.size should be less than # of rows
    init_array(); 
    
    for(int n = 0; n < data.size(); n++){
        for(int i = 0; i < data[n].length(); i++){
            _record[n][i] = data[n][i]; 
        }
       //_record[n][i] = '\0'; //making sure the arrays are null terminated
    }
} 

vector<string> FileRecord::get_record(){
    vector<string> returnVec; 
    for(int row = 0; row < MAX_ROWS && _record[row][0] != '\0'; row++){
        string mData = ""; 
        for(int col = 0; col < MAX_COLS && _record[row][col] != '\0'; col++){
            mData += _record[row][col]; 
        }
        returnVec.push_back(mData); 
    }
    return returnVec; 
}


long FileRecord::write(fstream& mFile){
    std::streampos gCount = mFile.tellg(); 
    mFile.seekg(gCount); //for now, just writing in beginning //
    for(int i = 0; i < MAX_ROWS; i++){
        mFile.write(*(_record + i), MAX_COLS + 1); 
    }

    std::streampos byteSize = mFile.tellg(); 
    recNum = byteSize / (MAX_ROWS * (MAX_COLS + 1)); //recNum--; //at its very least it will be one skewing evrything
    recNum--;
    return recNum; 
    //writes the record into file and increment record num 
} //returns the record number

long FileRecord::read(fstream& mFile, long recno){ //constraint assumption --> recno starts from 0 
    mFile.seekg((recno) * (MAX_ROWS * (MAX_COLS + 1))); 
    int pos = mFile.tellg(); 

    for(int row = 0; row < MAX_ROWS; row++){ 
        mFile.read(*(_record + row), MAX_COLS + 1);
    } 
    return mFile.tellg(); //for now ??
}//returns the number of bytes

#endif 