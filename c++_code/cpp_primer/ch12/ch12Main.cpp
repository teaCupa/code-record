//
// Created by teagm on 2023/4/15.
//

#include "ch12.h"
#include <iostream>
using namespace std;

int main() {
    ifstream is("E:\\clionIDE\\workstation\\cpp_primer\\ch12\\storyDataFile.txt");
    TextQuery tq(is);

    while(true){
        cout << "enter word to look for, or q to quit: \n";
        string s;
        if(!(cin >> s) || s=="q") break;
        print(cout,tq.query(s)) << endl;
    }
}

