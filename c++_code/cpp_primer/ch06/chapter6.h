//
// Created by teagm on 2023/4/14.
//

#ifndef CPP_PRIMER_CHAPTER6_H
#define CPP_PRIMER_CHAPTER6_H

int fact(int n);
int fact2(int n);

int interactive_fact();

template <typename T>
T abs_(T i){
    return i >= 0 ? i : -i;
}

#endif //CPP_PRIMER_CHAPTER6_H
