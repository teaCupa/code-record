//
// Created by teagm on 2023/4/14.
//

#include <iostream>
#include <vector>
#include <list>

using std::cout;using std::endl;using std::list;using std::copy;

template <typename Sequence>
void print(Sequence& seq){
    for(auto& i : seq){
        cout << i << " ";
    }
    cout << endl;
}

int main(){
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    // uses inserter
    list<int> lst1{10};
    copy(v.cbegin(),v.cend(),std::inserter(lst1,lst1.begin()));
    print(lst1);

    // uses back_inserter
    list<int> lst2{10};
    copy(v.cbegin(),v.cend(),std::back_inserter(lst2));
    print(lst2);

    // uses front_inserter
    list<int> lst3{10};
    copy(v.cbegin(),v.cend(),std::front_inserter(lst3));
    print(lst3);
}