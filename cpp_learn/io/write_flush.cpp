//
// Created by teagm on 2023/4/18.
//

#include<stdio.h>
#include<unistd.h>

int main()
{
    FILE *fp = fopen("./file.txt","a");
    if(fp == NULL)
    {
        printf("open file err!\n");
        return -1;
    }
    fwrite("hello",5,1,fp);
//	fflush(fp);
//	fclose(fp);  //buffer_ flush to disk

    return 0;
}