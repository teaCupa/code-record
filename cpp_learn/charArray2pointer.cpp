//
// Created by teagm on 2023/4/18.
//

#include<stdio.h>
#include<string.h>

int main()
{
    char ch[3][10];
    char* ch2[3];
    strcpy(ch[0],"hello");
//    ch[0]="hello";  //ERROR! ch[0] is array-type, can't assign

    //strcpy(ch2[0],"hello");
    ch2[0] ="hello";    //directly assign
    printf("%s %s\n",ch[0],ch2[0]);

    char* p= ch[0];
    char** p2 =ch2;   //cast
    printf("%s %s\n",p,p2[0]);
}