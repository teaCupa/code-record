//
// Created by teagm on 2023/4/16.
//

#ifndef CPP_PRIMER_QUOTE_H
#define CPP_PRIMER_QUOTE_H

#include <string>
#include <iostream>

class Quote {
    friend bool operator!=(const Quote& lhs, const Quote& rhs);
public:
    Quote(){ std::cout << "default constructing Quote\n"; }
    Quote(const std::string &b, double p) :
            bookNo(b), price(p) { std::cout << "Quote : constructor taking 2 parameters\n"; }
    //copy constructor
    Quote(const Quote& q) : bookNo(q.bookNo),price(q.price)
          { std::cout << "Quote: copy constructing\n"; }
    //move constructor
    Quote(Quote&& q)  : bookNo(std::move(q.bookNo)),price(q.price)
          { std::cout << "Quote: move constructing\n"; }
    // copy assignment
    Quote& operator=(const Quote& q){
        if(*this != q){
            bookNo = q.bookNo;
            price = q.price;
        }
        std::cout << "Quote: copy =() \n";
        return *this;
    }
    // move assignment
    Quote& operator=(Quote&& q) noexcept {
        if(*this != q)
        {
            bookNo = std::move(q.bookNo);
            price  = q.price;
        }
        std::cout << "Quote: move =!!!!!!!!! \n";
        return *this;
    }
    std::string   isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n*price; }
    virtual void debug() const;

    virtual ~Quote() { std::cout << "destructing Quote\n"; }

protected:
    double price = 10.0;
private:
    std::string bookNo;
};

bool inline operator!=(const Quote& lhs, const Quote& rhs){
    return lhs.bookNo != rhs.bookNo ||
                     lhs.price != rhs.price;
}


#endif //CPP_PRIMER_QUOTE_H
