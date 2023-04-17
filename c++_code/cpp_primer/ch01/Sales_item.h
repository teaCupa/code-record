//
// Created by teagm on 2023/4/13.
//

#ifndef CPP_PRIMER_SALES_ITEM_H
#define CPP_PRIMER_SALES_ITEM_H

#include <iostream>
#include <string>

class Sales_item {
    friend std::istream& operator>>(std::istream&,Sales_item&);
    friend std::ostream& operator<<(std::ostream&,const Sales_item&);
    friend bool operator==(const Sales_item& lhs,const Sales_item& rhs);

public:
    Sales_item() = default;
    explicit Sales_item(const std::string &bookno) : bookNo(bookno){}
    explicit Sales_item(std::istream &is) { is >> *this; }   //istream param's ctor, call operator>>

    std::string isbn() const { return bookNo; }
    double avg_price() const;

    // member binary operator: left-hand operand bound to implicit this pointer
    Sales_item& operator+=(const Sales_item&);

private:
    std::string bookNo;        // implicitly initialized to the empty string
    unsigned units_sold = 0;   // explicitly initialized
    double revenue = 0.0;      // 收入
};

std::istream& operator>>(std::istream& in,Sales_item& s){
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    // check that the inputs succeeded
    if(in)
        s.revenue = s.units_sold * price;
    else
        s = Sales_item();   // input failed: reset object to default state
    return in;
}

std::ostream& operator<<(std::ostream& out,const Sales_item& s){
    out << s.bookNo << " " << s.units_sold << " " << s.revenue << " " << s.avg_price();
    return out;
}

inline bool
operator==(const Sales_item& lhs,const Sales_item& rhs){
    // must be made a friend of Sales_item
    return lhs.bookNo == rhs.bookNo &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}

inline bool
operator!=(const Sales_item& lhs,const Sales_item& rhs){
    return !(lhs==rhs);
}

double Sales_item::avg_price() const {
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}

Sales_item& Sales_item::operator+=(const Sales_item& rhs) {
    if (bookNo != rhs.bookNo){
        std::cerr << "operator+= assumes that both objects refer to the same ISBN" << std::endl;
        exit(-1);
    }
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// nonmember binary operator: must declare a parameter for each operand
Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs){
    Sales_item ret(lhs);
    ret += rhs;
    return ret;
}

#endif //CPP_PRIMER_SALES_ITEM_H
