#include <iostream>
#include<cassert>
#include <memory>

/**
 * in unique_ptr.h:
 *    // Disable copy from lvalue.
 *    unique_ptr(const unique_ptr&) = delete;
 *    unique_ptr& operator=(const unique_ptr&) = delete;
 * so you can't  copy from lvalue
 */


struct Foo {
    int id;
    Foo(int id) : id(id) { std::cout << "Foo " << id << '\n'; }
    ~Foo() { std::cout << "~Foo " << id << '\n'; }

    friend
     std::ostream& operator<<(std::ostream& os,const Foo& f);
};

 std::ostream& operator<<(std::ostream& os,const Foo& f){
        os<<f.id;
        return os;
 }

int main()
{
    std::unique_ptr<Foo> p1( new Foo(1) );

    {
        std::cout << "Creating new Foo...\n";
        std::unique_ptr<Foo> p2( new Foo(2) );
        // p1 = p2; // Error ! can't copy unique_ptr, because unique_ptr& operator=(const unique_ptr&) = delete;
        p1 = std::move(p2);  //仅允许move assignment ,控制权转移, call ~Foo()
        assert(p2==nullptr);
        assert(p1->id==2);

        std::cout << "About to leave inner block... " <<std::endl;

        // Foo instance will continue to live,
        // despite p2 going out of scope
    }

    std::cout << "About to leave program...\n";

}