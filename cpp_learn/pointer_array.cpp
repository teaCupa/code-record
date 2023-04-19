//
// Created by teagm on 2023/4/18.
//

#include <iostream>

int main()
{
    int (*p)[2];
    int b[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    p = b;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++)
            std::cout << p[i][j]; //cout << *(*(p+i)+j)
        std::cout << std::endl;
    }

    int* p2[2];
    p2[0]=new int[3]{1,2,3};
    p2[1]=new int[3]{4,5,6};

    std::cout<<p2<<" "<<*p2<<std::endl;   //p2 is a two-dimension address, *p2 is a one-dimension address
    std::cout<<*(*(p2+1)+2);            //p2[1][2]

}