//
// Created by teagm on 2023/4/18.
//

#include<stdio.h>

typedef struct{
    int a;
    int b;
}point;

void fun(int *a,int *b)
{
    int t;
    int *p;//p is a address
    t=*a;  p=a;
    *a=*b;
    *b=t;
    printf("t=%d  ,*p=%d, p=%d\n",t,*p,p);//*p is a number
    printf("a=%d,&p=%d\n",a,&p);//p是一个address ,&p是p的地址
}

void fun2(int &m,int &n)
{
    int tmp=m;
    m=n;
    n=tmp;
    printf("%d,%d\n",m,&m);
}

void fun3(point* p){
    int tmp=p->a;
    p->a=p->b;
    p->b=tmp;
}

int main(){
    int x=1,y=3;
    fun(&x,&y);
    printf("%d,%d\n",x,y);
    printf("address:%d,%d\n",&x,&y);
    printf("---------\n");

    int a=1,b=2;
    fun2(a,b);
    printf("a=%d,b=%d\n",a,b);
    printf("=========\n");

    point p;
    p.a=1;
    p.b=2;
    fun3(&p);
    printf("a=%d,b=%d",p.a,p.b);
    printf(">>>>>>>>>\n");

    return 0;
}

