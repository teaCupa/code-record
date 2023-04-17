//
// Created by teagm on 2023/4/13.
//

#include "Sales_item.h"

void q_1(){
    Sales_item s1;
    Sales_item s2;
    std::cin >> s1;
    std::cout << s1 << std::endl;
    std::cin >> s2;
    std::cout << s2 << std::endl;
    std::cout << "sum of sale items: " << s1 + s2 << std::endl;
}

void q_2(){
    Sales_item sum_item;
    std::cin >> sum_item;
    for(Sales_item item;std::cin>>item;std::cout<<item<<std::endl){  //linux上CTRL+D退出该循环
        if(item.isbn()=="foo") break;
        sum_item += item;
    }
    std::cout << "sum of sale items: " << sum_item<<std::endl;
}

void q_3(){
    Sales_item total;
    if(std::cin>>total){    //linux上CTRL+D使该输入判断为false
        Sales_item trans;
        //将isbn号相同的Sales_item进行累加
        while(std::cin >> trans){
            if(total.isbn() == trans.isbn())
                total += trans;
            else {
                std::cout << "total: " << total <<std::endl;
                total = trans;
            }
        }
        std::cout << "total: " << total <<std::endl;
    }else{
        std::cout << "no data input..." << std::endl;
    }
}

void q_4(){
    std::cout << "\n4. use istream as parameter: " << std::endl;
    std::cout << "----------------" << std::endl;
    Sales_item s4(std::cin);
}

//输入Sales_item
//0-201-78345-X 3 20.00
//0-201-78345-X 2 25.00
//foo           2 15.00
int main(){
//    q_1();
//    q_2();
//    q_3();
    q_4();
}