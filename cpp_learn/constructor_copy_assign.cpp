//
// Created by teagm on 2023/4/18.
//

#include<iostream>
#include <utility>

/**
 * // MyClass is not copyable from lvalue.
 * MyClass(const MyClass&) = delete;
 * MyClass& operator=(const MyClass&) = delete;
 *
 * but if you want to copy from rvalue, you must define
 *    MyClass(MyClass&&) noexcept { }    and
 *    MyClass& operator=(MyClass&&) noexcept;
 */

class Env{
public:
    Env()=default;
    Env(std::string s):s_(std::move(s)){};
    Env(const Env&) = delete ;    //not allow 'Env env2(env)' to copy
    Env& operator=(const Env&) = delete;  //not allow 'env4=env3' assign
//    Env& operator=(const Env& other){
//        std::cout <<"operator="<<std::endl;
//        std::cout <<"this.s_: "<<s_<<" , other.s_: "<<other.s_ <<std::endl;
//        if(this!= &other){
//            s_ =other.s_;
//        }
//        return *this;
//    }

   Env(Env&& rhs) noexcept {
       // ...
   }

    Env& operator=(Env&& rhs) noexcept {
       // ...
    }

    std::string s_;
};


int main()
{
    Env env;
    //Env env2(env);    //Env(const Env&) = delete
    //Env env2=env;   //Env(const Env&) = delete

    std::cout<<"-----\n";

    Env env3("hi");

    Env env4("hello");
    std::cout <<"env4.s_: "<<env4.s_<<std::endl;
//    env4 =env3;    //operator=
//    std::cout <<"env4.s_: "<<env4.s_ <<std::endl;

    Env env5 = std::move(env3);
//    std::cout <<"env5.s_: "<<env5.s_ <<std::endl;
}
