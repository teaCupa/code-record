//
// Created by teagm on 2023/4/16.
//

#include "quote.h"


void Quote::debug() const
{
    std::cout //<< "data members of this class:\n"
            << "bookNo= " <<this->bookNo << " "
            << "price= " <<this->price<< " \n";
}
