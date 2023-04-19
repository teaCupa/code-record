//
// Created by teagm on 2023/4/18.
//

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct obj{
    int a;
};

int main(){
// struct obj*  o = malloc(sizeof(int));
//   printf("address: %p \n",o);

    int* intp = (int*) malloc(sizeof(int));
    intp = static_cast<int *>(realloc(intp, sizeof(int) * 3));  //after realloc,intp mem is sizeof(int)*3=12bytes
    for(int i=0;i<3;i++)
        intp[i] =100+i;

    int* addr= intp;
    *(addr+3)=3;
    *(addr+4)=4;

    free(intp);   //free intp[0] and intp[1] and intp[2]

    printf("after free intp[0~2]...\n");
    for(int i=0;i<5;i++)
        printf("addr[%d]= %d\n",i, *(addr+i));
    printf("the addr[2,3] is fuck number,because they have been free!\nmem align (8byte)  means free addr[2] with addr[3]");
}
