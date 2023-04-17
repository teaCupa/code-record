//
// Created by teagm on 2023/4/16.
//

#include "disc_quote.h"

double Disc_quote::net_price(std::size_t n) const {
    return n*price*(n>=quantity ? 1-discount:1 );
};