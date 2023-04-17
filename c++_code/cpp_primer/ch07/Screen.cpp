//
// Created by teagm on 2023/4/14.
//

#include "Screen.h"


int main(){
    Screen myScreen(5,5,'X');
    myScreen.move(4,0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.set(2,2,'O');
    myScreen.display(std::cout);
}

