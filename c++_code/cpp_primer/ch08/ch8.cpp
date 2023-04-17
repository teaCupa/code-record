//
// Created by teagm on 2023/4/14.
// 标准IO库

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
using namespace std;

void loading(){
    for (int i = 0; i < 11; i++){
        cout << "loading " << (i * 10) << "%" << endl;
        sleep(1);
    }
    cout << "loaded!      " << endl;
}

void file_io(){
    string inFileName="cmake_install.cmake";
    string outFileName="test_out_file";
    ifstream infile(inFileName.c_str());
    ofstream outfile(outFileName.c_str());
    if(!infile)
        cerr << "err: unable to open input file: " << inFileName << endl;
    else{
        // 按词读取
/*        string word;
        while(infile>>word)
            cout << word <<endl;*/
        // 按行读取
        string line;
        while(getline(infile,line)){
            cout << line << endl;
            // 按行写入
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();
}

int main(){
//    loading();
    file_io();
}