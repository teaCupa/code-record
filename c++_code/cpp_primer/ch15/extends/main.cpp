//
// Created by teagm on 2023/4/16.
//

#include "disc_quote.h"


int main(){
    Disc_quote dq;
    Disc_quote dq2("isbn123",15.0,3,0.2);
    dq2 = std::move(dq2);
}

