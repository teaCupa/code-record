//
// Created by teagm on 2023/4/18.
//

#include<iostream>
#include<cstring>

/**
 *  when struct object is deleted, its children
 *     age and name are auto destroyed, but card object is a new pointer created by you,
 *         you must delete it by yourself
 */

struct card{
    long id;
};

struct student{
    int age;
    char name[10];
    struct card* card;
};


int main()
{
    student* stu =new student();
    stu->age=1;
    strcpy(stu->name,"zhang");
    card* card_ =new card();
    card_->id=2;
    stu->card=card_;
    delete stu;

    std::cout<<card_->id;
    delete card_;
}
